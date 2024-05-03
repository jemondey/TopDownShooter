// Fill out your copyright notice in the Description page of Project Settings.


#include "VGunBase.h"
#include "VCharacter.h"

// Sets default values
AVGunBase::AVGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
	CarryAmmoAmount = 0;
}

// Called when the game starts or when spawned
void AVGunBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmoAmount = MaxAmmoAmount;
	bCanShoot = true;
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
		FVector Location = MeshComp->GetSocketLocation("Fire_Socket");
		FRotator Rotation = (CH->GetPointUnderCursor() - Location).Rotation();
		float RotationOffsetMin = InstigatorActor->GetActorRotation().Yaw - 5;
		float RotationOffsetMax = InstigatorActor->GetActorRotation().Yaw;
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
	/*if (!bIsAutoFire)
	{
		Shoot();
		return;
	}*/
	if (ShootHandle.IsValid())
	{
		InstigatorPawn->GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AVGunBase::Shoot, FireRate, bIsAutoFire);
	}
}

void AVGunBase::ReleaseTrigger(APawn* InstigatorPawn)
{
	if (ShootHandle.IsValid())
	{
		InstigatorPawn->GetWorld()->GetTimerManager().ClearTimer(ShootHandle);
	}
}

void AVGunBase::TryReload(APawn* InstigatorPawn)
{
	if (CarryAmmoAmount <= 0)
	{
		return;
	}

	if (CurrentAmmoAmount < MaxAmmoAmount)
	{
		bCanShoot = false;
		InstigatorPawn->GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &AVGunBase::Reload, ReloadTime);
	}
}

void AVGunBase::Reload()
{
	int32 AmountToLoad = MaxAmmoAmount - CurrentAmmoAmount;
	AmountToLoad = FMath::Clamp(AmountToLoad, 0, CarryAmmoAmount);
	CarryAmmoAmount -= AmountToLoad;
	CurrentAmmoAmount += AmountToLoad;
	OnAmmoChanged.Broadcast(this, CurrentAmmoAmount, CarryAmmoAmount);
	bCanShoot = true;
}

void AVGunBase::SetCarryAmmoAmount(int32 Amount)
{
	CarryAmmoAmount += Amount;
	OnAmmoChanged.Broadcast(this, CurrentAmmoAmount, CarryAmmoAmount);
}
