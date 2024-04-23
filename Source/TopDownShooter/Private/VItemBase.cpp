// Fill out your copyright notice in the Description page of Project Settings.


#include "VItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "VItemDataAsset.h"
#include "VInventoryComponent.h"

// Sets default values
AVItemBase::AVItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	
	SphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	RootComponent = SphereComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AVItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVItemBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (ItemDataAsset)
	{
		UVItemDataAsset* DA = Cast<UVItemDataAsset>(ItemDataAsset);
		MeshComp->SetStaticMesh(DA->StaticMesh);
		ActorToAdd = DA->ActorToAdd;
		SlotNum = DA->SlotNum;
		HandSocket = DA->HandSocket;
		CarrySocket = DA->CarrySocket;
	}
}

// Called every frame
void AVItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVItemBase::Interact_Implementation(APawn* InstigatorPawn)
{
	UVItemDataAsset* DA = Cast<UVItemDataAsset>(ItemDataAsset);
	AActor* InstigatorActor = Cast<AActor>(InstigatorPawn);

	FVector Location = InstigatorActor->GetActorLocation();
	FRotator Rotation = InstigatorActor->GetActorRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = InstigatorPawn;
	SpawnParams.Owner = InstigatorPawn;

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToAdd, Location, Rotation, SpawnParams);
	UVInventoryComponent* CMP = Cast<UVInventoryComponent>(InstigatorActor->FindComponentByClass(UVInventoryComponent::StaticClass()));
	CMP->GrabItem(SpawnedActor, DA, SlotNum, CarrySocket);
}

FName AVItemBase::GetCarrySocketName()
{
	return CarrySocket;
}

FName AVItemBase::GetHandSocketName()
{
	return HandSocket;
}
