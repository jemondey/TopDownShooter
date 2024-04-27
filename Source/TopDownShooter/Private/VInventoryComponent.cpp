// Fill out your copyright notice in the Description page of Project Settings.


#include "VInventoryComponent.h"
#include "GameFramework/Character.h"
#include "VItemBase.h"
#include "VItemDataAsset.h"
#include "VGunBase.h"

// Sets default values for this component's properties
UVInventoryComponent::UVInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxSlots = 5;
	SlotsArray.Init(nullptr, MaxSlots);
	SlotsDataArray.Init(nullptr, MaxSlots);
}

// Called when the game starts
void UVInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString slt1 = SlotsArray[0] ? SlotsArray[0]->GetName() : "null";
	FString slt2 = SlotsArray[1] ? SlotsArray[1]->GetName() : "null";
	FString slt3 = SlotsArray[2] ? SlotsArray[2]->GetName() : "null";
	FString slt4 = SlotsArray[3] ? SlotsArray[3]->GetName() : "null";
	FString slt5 = SlotsArray[4] ? SlotsArray[4]->GetName() : "null";

	FString Slot1 = "1 - " + slt1;
	GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, Slot1);
	FString Slot2 = "2 - " + slt2;
	GEngine->AddOnScreenDebugMessage(3, 1, FColor::Red, Slot2);
	FString Slot3 = "3 - " + slt3;
	GEngine->AddOnScreenDebugMessage(4, 1, FColor::Red, Slot3);
	FString Slot4 = "4 - " + slt4;
	GEngine->AddOnScreenDebugMessage(5, 1, FColor::Red, Slot4);
	FString Slot5 = "5 - " + slt5;
	GEngine->AddOnScreenDebugMessage(6, 1, FColor::Red, Slot5);
	//Only for the moment. Will be deleted after UI implementation
}

void UVInventoryComponent::ChangeItem(int32 Slot)
{
	int32 SlotInArray = Slot - 1;
	if (SlotInArray > MaxSlots - 1 || SlotInArray < 0)
	{
		return;
	}
	if (SlotsArray[SlotInArray] == nullptr)
	{
		return;
	}

	NewItem = SlotsArray[SlotInArray];
	NewItemData = SlotsDataArray[SlotInArray];
	if (NewItemData == nullptr || NewItem == nullptr || !NewItemData->GetCanBeCarried())
	{
		return;
	}

	if (CurrentItem && CurrentItem->IsAttachedTo(GetOwner()))
	{
		FName CarrySocket = CurrentItemData->GetCarrySocketName();
		FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules::KeepRelativeTransform;
		CurrentItem->DetachFromActor(DetachmentRules);
		AttachItem(CurrentItem, CurrentItemData, CarrySocket);
	}

	FName HandSocket = NewItemData->GetHandSocketName();
	AttachItem(NewItem, NewItemData, HandSocket);
	CurrentItem = NewItem;
	CurrentItemData = NewItemData;
	OnItemChanged.Broadcast(Cast<ACharacter>(GetOwner()), Slot);
}

void UVInventoryComponent::AssignSlot(AActor* Item, UVItemDataAsset* DataAsset, int32 Slot)
{
	int32 SlotInArray = Slot - 1;
	if (Item == nullptr)
	{
		return;
	}
	if (SlotInArray > MaxSlots - 1)
	{
		return;
	}

	if (Slot == 0)
	{
		for (int32 Index = 0; SlotsArray.Num() - 1; Index++)
		{
			AActor* Actor = SlotsArray[Index];
			if (Actor == nullptr)
			{
				NewItem = Item;
				NewItemData = DataAsset;
				SlotsArray[Index] = Item;
				SlotsDataArray[Index] = DataAsset;
				return;
			}
			return;
		}
	}
	NewItem = Item;
	NewItemData = DataAsset;
	SlotsArray[SlotInArray] = Item;
	SlotsDataArray[SlotInArray] = DataAsset;
}

void UVInventoryComponent::AttachItem(AActor* Item, UVItemDataAsset* DataAsset, FName SocketName)
{
	if (Item == nullptr)
	{
		return;
	}
	if (!DataAsset->GetCanBeCarried())
	{
		return;
	}

	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepRelative,
		true);
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	Item->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentRules, SocketName);
}

void UVInventoryComponent::GrabItem(AActor* Item, UVItemDataAsset* DataAsset, int32 Slot, FName CarrySocket)
{
	if (Item == nullptr)
	{
		return;
	}

	AssignSlot(Item, DataAsset, Slot);
	AttachItem(Item, DataAsset, CarrySocket);
}

AActor* UVInventoryComponent::GetCurrentItem()
{
	if(CurrentItem != nullptr)
	{
		return CurrentItem;
	}
	return nullptr;
}

AActor* UVInventoryComponent::FindActor(TSubclassOf<AActor> ActorToFind)
{
	if (!ensure(ActorToFind))
	{
		return nullptr;
	}

	for (AActor* Actor : SlotsArray)
	{
		if (Actor && Actor->GetClass() == ActorToFind)
		{
			return Actor;
		}
	}
	return nullptr;
}