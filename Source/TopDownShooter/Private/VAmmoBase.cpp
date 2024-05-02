// Fill out your copyright notice in the Description page of Project Settings.


#include "VAmmoBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "VAttributesComponent.h"
#include "Components/SphereComponent.h"

AVAmmoBase::AVAmmoBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = SphereComp;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComp->SetCollisionProfileName("Projectile");
	MeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MeshComp->SetupAttachment(RootComponent);

	AmmoDamage = -50.f;
	AmmoSpeed = 2000.f;
	MovementComp->InitialSpeed = AmmoSpeed;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;
}

void AVAmmoBase::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AVAmmoBase::OnActorOverlap);
}

void AVAmmoBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UVAttributesComponent* AttributeComp = Cast<UVAttributesComponent>(OtherActor->FindComponentByClass(UVAttributesComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(), AmmoDamage);
			Destroy();
		}
	}
}