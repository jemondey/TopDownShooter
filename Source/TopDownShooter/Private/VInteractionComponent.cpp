// Fill out your copyright notice in the Description page of Project Settings.


#include "VInteractionComponent.h"
#include "VGameplayInterface.h"
#include "VCharacter.h"
#include "VInventoryComponent.h"

// Sets default values for this component's properties
UVInteractionComponent::UVInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TraceLength = 1000.f;
	TraceSphereRadius = 10.f;
}

void UVInteractionComponent::Interact()
{
	AVCharacter* Owner = Cast<AVCharacter>(GetOwner());
	FVector CursorPoint = Owner->GetPointUnderCursor();
	float Distance = FVector::Dist(CursorPoint, Owner->GetActorLocation());
	if (Distance > TraceLength)
	{
		return;
	}

	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	FHitResult Hit;
	FVector Start = Owner->GetCameraLocation();
	FVector End = Start + (((CursorPoint - Start).Rotation()).Vector().GetSafeNormal() * 1000);
	FCollisionShape Shape;
	Shape.MakeSphere(TraceSphereRadius);
	GetWorld()->SweepSingleByObjectType(Hit, Start, End, FQuat::Identity, QueryParams, Shape);
	AActor* HitActor = Hit.GetActor();

	if (HitActor)
	{
		if(HitActor->Implements<UVGameplayInterface>())
		{
			APawn* OwnerPawn = Cast<APawn>(GetOwner());
			IVGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
			return;

		}
	}
	
}

