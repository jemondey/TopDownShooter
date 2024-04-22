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
	MaxAmmoAmount = 15;
	CurrentAmmoAmount = MaxAmmoAmount;
	bCanShoot = true;
}

void AVGunBase::Attack_Implementation(APawn* InstigatorPawn)
{
	PullTrigger(InstigatorPawn);
}

// Called when the game starts or when spawned
void AVGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVGunBase::Shoot()
{
	if (CurrentAmmoAmount <= 0)
	{
		FString Message = "OUT OF AMMO!";
		GEngine->AddOnScreenDebugMessage(0, 0.4f, FColor::Red, Message);
		return;
	}

	FString Message = "Pow!";
	GEngine->AddOnScreenDebugMessage(0, 0.4f, FColor::Green, Message);
	if (AmmoClass)
	{
		AVCharacter* CH = Cast<AVCharacter>(InstigatorActor);
		FVector Location = CH->GetMesh()->GetAttachChildren().Last()->GetSocketLocation("Fire_Socket");
		FRotator Rotation = (CH->GetPointUnderCursor() - Location).Rotation();
		Rotation.Pitch = 0;
		Rotation.Roll = 0;
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = Cast<APawn>(InstigatorActor);
		SpawnParams.Owner = InstigatorActor;

		if(InstigatorActor->GetWorld()->SpawnActor<AActor>(AmmoClass, Location, Rotation, SpawnParams))
		{
			FString MessageG = "Spawned!";
			GEngine->AddOnScreenDebugMessage(1, 0.4f, FColor::Green, MessageG);
			CurrentAmmoAmount -= 1;
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
	if (CurrentAmmoAmount < MaxAmmoAmount)
	{
		FString Message = "RELOADING";
		GEngine->AddOnScreenDebugMessage(0, ReloadTime - 0.2f, FColor::Red, Message);
		bCanShoot = false;
		InstigatorPawn->GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AVGunBase::Reload, ReloadTime);
	}
}

void AVGunBase::Reload()
{
	FString Message = "RELOADED";
	GEngine->AddOnScreenDebugMessage(0, 0.4f, FColor::Green, Message);
	bCanShoot = true;
	CurrentAmmoAmount = MaxAmmoAmount;
}

// Called every frame
void AVGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

