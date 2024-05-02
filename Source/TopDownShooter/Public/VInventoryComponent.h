// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VInventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemChanged, ACharacter*, OwningCharacter, int32, SlotNumber, AActor*, CurrentItem);

class UVItemDataAsset;
class AVGunBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UVInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVInventoryComponent();

	UPROPERTY(BlueprintAssignable)
	FOnItemChanged OnItemChanged;
	UFUNCTION(BlueprintCallable)
	void ChangeItem(int32 Slot);

	void GrabItem(AActor* Item, UVItemDataAsset* DataAsset, int32 Slot, FName CarrySocket);
	void UseHealBox();
	AActor* GetCurrentItem();
	AActor* FindActor(TSubclassOf<AActor> ActorToFind);
	void SetSlotsNull(int32 SlotNum);

protected:

	int32 MaxSlots;
	TArray<AActor*> SlotsArray;
	TArray<UVItemDataAsset*> SlotsDataArray;
	AActor* CurrentItem;
	AActor* NewItem;
	UVItemDataAsset* CurrentItemData;
	UVItemDataAsset* NewItemData;

	void AssignSlot(AActor* Item, UVItemDataAsset* DataAsset, int32 Slot);
	void AttachItem(AActor* Item, UVItemDataAsset* DataAsset, FName SocketName);
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
