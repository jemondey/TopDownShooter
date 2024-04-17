// Fill out your copyright notice in the Description page of Project Settings.


#include "VCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AVCharacter::AVCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(RootComponent);
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

	if(PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 30.f, 16, FColor::Red);
		RotatePlayer(HitResult.ImpactPoint);
	}

}

// Called to bind functionality to input
void AVCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVCharacter::MoveRight);

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

void AVCharacter::RotatePlayer(FVector Direction)
{
	FVector ToTarget = Direction - GetMesh()->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw - 90, 0.0f);
	GetMesh()->SetWorldRotation(FMath::RInterpTo(
		GetMesh()->GetComponentRotation(), 
		LookAtRotation, 
		UGameplayStatics::GetWorldDeltaSeconds(this), 
		10.f));
}
