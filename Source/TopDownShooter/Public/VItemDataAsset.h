// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VItemDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TOPDOWNSHOOTER_API UVItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	class UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToAdd;
	UPROPERTY(EditAnywhere)
	int32 SlotNum;
	UPROPERTY(EditAnywhere)
	FName HandSocket;
	UPROPERTY(EditAnywhere)
	FName CarrySocket;
	UPROPERTY(EditAnywhere)
	bool bCanBeCarried;

	FName GetHandSocketName();
	FName GetCarrySocketName();
	bool GetCanBeCarried();
	
};
