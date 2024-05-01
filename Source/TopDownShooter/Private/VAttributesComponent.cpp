// Fill out your copyright notice in the Description page of Project Settings.


#include "VAttributesComponent.h"


UVAttributesComponent::UVAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	HealthMax = 100;
	Health = HealthMax;
}

void UVAttributesComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UVAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString Mesg = "Health = " + FString::SanitizeFloat(Health);
	GEngine->AddOnScreenDebugMessage(12, 1, FColor::Red, Mesg);
}

void UVAttributesComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	Health += Delta;
	Health = FMath::Clamp(Health, 0 , HealthMax);
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);
}

UVAttributesComponent* UVAttributesComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<UVAttributesComponent>();
	}
	return nullptr;
}

bool UVAttributesComponent::IsActorAlive(AActor* Actor)
{
	UVAttributesComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}
	return false;
}

bool UVAttributesComponent::IsAlive()
{
	return Health > 0.0f;
}
