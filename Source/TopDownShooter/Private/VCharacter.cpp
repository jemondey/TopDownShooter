// Fill out your copyright notice in the Description page of Project Settings.


#include "VCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "VInteractionComponent.h"
#include "VAttributesComponent.h"
#include "VInventoryComponent.h"
#include "VGunBase.h"
#include "VGameplayInterface.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AVCharacter::AVCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	InteractionComp = CreateDefaultSubobject<UVInteractionComponent>("InteractionComponent");
	AttributesComp = CreateDefaultSubobject<UVAttributesComponent>("AttributesComponent");
	InventoryComp = CreateDefaultSubobject<UVInventoryComponent>("InventoryComponent");
	
	SpringArmComp->bUsePawnControlRotation = false;
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);

}

// Called when the game starts or when spawned
void AVCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
}


// Called every frame
void AVCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim();
}

// Called to bind functionality to input
void AVCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVCharacter::MoveRight);
	PlayerInputComponent->BindAxis("SelectItem", this, &AVCharacter::SelectItem);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AVCharacter::Interact);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AVCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AVCharacter::StopAttack);
	PlayerInputComponent->BindAction("Reload", IE_Released, this, &AVCharacter::Reload);
	PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &AVCharacter::Heal);
}

void AVCharacter::MoveForward(float Value)
{
	FVector ControlVec = CameraComp->GetUpVector();
	AddMovementInput(ControlVec, Value);
}

void AVCharacter::MoveRight(float Value)
{
	FVector ControlVec = CameraComp->GetRightVector();
	AddMovementInput(ControlVec, Value);
}

FVector AVCharacter::GetPointUnderCursor()
{
	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 16, FColor::Red);
		return HitResult.ImpactPoint;
	}
	return FVector::ZeroVector;
}

FVector AVCharacter::GetCameraLocation()
{
	return CameraComp->GetComponentLocation();
}

void AVCharacter::RotatePlayer(FVector Direction)
{
	FVector ToTarget = Direction - GetMesh()->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
	SetActorRotation(LookAtRotation);
}

void AVCharacter::Interact()
{
	InteractionComp->Interact();
}

void AVCharacter::SelectItem(float Value)
{
	int32 SlotNum = Value;
	InventoryComp->ChangeItem(SlotNum);
}

void AVCharacter::Heal()
{
	InventoryComp->UseHealBox();
}

void AVCharacter::Attack()
{
	AVGunBase* Gun = Cast<AVGunBase>(InventoryComp->GetCurrentItem());
	if (ensure(Gun))
	{
		Gun->PullTrigger(this);
	}
}

void AVCharacter::StopAttack()
{
	AVGunBase* Gun = Cast<AVGunBase>(InventoryComp->GetCurrentItem());
	if (ensure(Gun))
	{
		Gun->ReleaseTrigger(this);
	}
}

void AVCharacter::Reload()
{
	if (InventoryComp->GetCurrentItem() == nullptr)
	{
		return;
	}

	AVGunBase* Gun = Cast<AVGunBase>(InventoryComp->GetCurrentItem());
	if (ensure(Gun))
	{
		Gun->TryReload(this);
	}
}

void AVCharacter::Aim()
{
	FVector Direction = GetPointUnderCursor();
	RotatePlayer(Direction);
}