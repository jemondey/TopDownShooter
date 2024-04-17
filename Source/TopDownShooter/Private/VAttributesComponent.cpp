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


}

void UVAttributesComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	Health += Delta;
	Health = FMath::Clamp(Health, 0 , HealthMax);
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);
}

