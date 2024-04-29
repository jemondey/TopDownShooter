// Fill out your copyright notice in the Description page of Project Settings.


#include "VGunBase.h"
#include "VCharacter.h"

// Sets default values
AVGunBase::AVGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
	bCanShoot = true;
	CarryAmmoAmount = 0;
}

void AVGunBase::Attack_Implementation(APawn* InstigatorPawn)
{
	PullTrigger(InstigatorPawn);
}

// Called when the game starts or when spawned
void AVGunBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmoAmount = MaxAmmoAmount;
}

void AVGunBase::Shoot()
{
	if (CurrentAmmoAmount <= 0)
	{
		return;
	}

	if (AmmoClass)
	{
		AVCharacter* CH = Cast<AVCharacter>(InstigatorActor);
		FVector Location = CH->GetMesh()->GetAttachChildren().Last()->GetSocketLocation("Fire_Socket");
		FRotator Rotation = (CH->GetPointUnderCursor() - Location).Rotation();
		float RotationOffsetMin = CH->GetActorRotation().Yaw - 5;
		float RotationOffsetMax = CH->GetActorRotation().Yaw + 5;
		Rotation.Yaw = FMath::Clamp(Rotation.Yaw, RotationOffsetMin, RotationOffsetMax);
		Rotation.Pitch = 0;
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = Cast<APawn>(InstigatorActor);
		SpawnParams.Owner = InstigatorActor;

		if(InstigatorActor->GetWorld()->SpawnActor<AActor>(AmmoClass, Location, Rotation, SpawnParams))
		{
			CurrentAmmoAmount -= 1;
			CurrentAmmoAmount = FMath::Clamp(CurrentAmmoAmount, 0, MaxAmmoAmount);
			OnAmmoChanged.Broadcast(this, CurrentAmmoAmount, CarryAmmoAmount);
		}
	}
}

void AVGunBase::PullTrigger(APawn* InstigatorPawn)
{
	if (!bCanShoot)
	{
		return;
	}

	InstigatorActor = InstigatorPawn;
	InstigatorPawn->GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AVGunBase::Shoot, FireRate, bIsAutoFire, 0.f);
}

void AVGunBase::ReleaseTrigger(APawn* InstigatorPawn)
{
	InstigatorPawn->GetWorld()->GetTimerManager().ClearTimer(ShootHandle);
}

void AVGunBase::TryReload(APawn* InstigatorPawn)
{
	if (CarryAmmoAmount <= 0)
	{
		return;
	}

	if (CurrentAmmoAmount < MaxAmmoAmount)
	{
		FString Message = "RELOADING";
		GEngine->AddOnScreenDebugMessage(0, ReloadTime - 0.2f, FColor::Red, Message);
		bCanShoot = false;
		InstigatorPawn->GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AVGunBase::Reload, ReloadTime);
	}
}

void AVGunBase::SetCarryAmmoAmount(int32 Amount)
{
	CarryAmmoAmount += Amount;
	OnAmmoChanged.Broadcast(this, CurrentAmmoAmount, CarryAmmoAmount);
}

void AVGunBase::Reload()
{
	FString Message = "RELOADED";
	GEngine->AddOnScreenDebugMessage(0, 0.4f, FColor::Green, Message);
	bCanShoot = true;
	int32 AmountToLoad = MaxAmmoAmount - CurrentAmmoAmount;
	AmountToLoad = FMath::Clamp(AmountToLoad, 0, CarryAmmoAmount);
	CarryAmmoAmount -= AmountToLoad;
	CurrentAmmoAmount += AmountToLoad;
	OnAmmoChanged.Broadcast(this, CurrentAmmoAmount, CarryAmmoAmount);
}

// Called every frame
void AVGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

