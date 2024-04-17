// Fill out your copyright notice in the Description page of Project Settings.


#include "VItemBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AVItemBase::AVItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void AVItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVItemBase::Interact_Implementation(APawn* InstigatorPawn)
{
}
