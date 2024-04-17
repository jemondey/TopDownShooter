// Fill out your copyright notice in the Description page of Project Settings.


#include "VInteractionComponent.h"
#include "VGameplayInterface.h"
#include "VCharacter.h"

// Sets default values for this component's properties
UVInteractionComponent::UVInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TraceLength = 1000.f;
	TraceSphereRadius = 10.f;
}


// Called when the game starts
void UVInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UVInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UVInteractionComponent::Interact()
{
	AVCharacter* Owner = Cast<AVCharacter>(GetOwner());
	FVector CursorPoint = Owner->GetPointUnderCursor();
	if (CursorPoint == Owner->GetActorLocation())
	{
		return;
	}

	FHitResult Hit;
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = CursorPoint;
	FCollisionShape Shape;
	Shape.MakeSphere(TraceSphereRadius);
	GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECollisionChannel::ECC_Visibility, Shape);
	AActor* HitActor = Hit.GetActor();

	if (HitActor)
	{
		if(HitActor->Implements<UVGameplayInterface>())
		{
			APawn* OwnerPawn = Cast<APawn>(GetOwner());
			IVGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
			DrawDebugSphere(GetWorld(), End, 30.f, 16, FColor::Green);
		}
		DrawDebugSphere(GetWorld(), End, 30.f, 16, FColor::Red);
	}
}

