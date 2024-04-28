// Fill out your copyright notice in the Description page of Project Settings.


#include "VAttributesComponent.h"
#include "VItem_HealBox.h"
#include "VInventoryComponent.h"

// Sets default values
AVItem_HealBox::AVItem_HealBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetupAttachment(RootComponent);

	CurrentAmount = 1;
}

// Called when the game starts or when spawned
void AVItem_HealBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVItem_HealBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVItem_HealBox::Heal(AActor* ActorToHeal)
{
	UVAttributesComponent* AttributeComp = Cast<UVAttributesComponent>(ActorToHeal->GetComponentByClass(UVAttributesComponent::StaticClass()));
	if (AttributeComp)
	{
		AttributeComp->ApplyHealthChange(ActorToHeal, HealAmount);
		ReduceHeal(ActorToHeal);
	}
}

void AVItem_HealBox::AddHeal()
{
	CurrentAmount += AmountToGive;
}

void AVItem_HealBox::ReduceHeal(AActor* Actor)
{
	CurrentAmount -= 1;
	if (CurrentAmount <= 0)
	{
		UVInventoryComponent* InvComp = Cast<UVInventoryComponent>(Actor->GetComponentByClass(UVInventoryComponent::StaticClass()));
		if(InvComp)
		{
			InvComp->SetSlotsNull(3);
			Destroy();
		}
	}
}