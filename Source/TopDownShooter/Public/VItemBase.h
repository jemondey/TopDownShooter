// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VGameplayInterface.h"
#include "VItemBase.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AVItemBase : public AActor, public IVGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVItemBase();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	FName GetCarrySocketName();
	FName GetHandSocketName();

protected:

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditInstanceOnly, Category = "DataAsset")
	UDataAsset* ItemDataAsset;

	UPROPERTY(VisibleAnywhere, Category = "DataAsset")
	TSubclassOf<AActor> ActorToAdd;
	UPROPERTY(VisibleAnywhere, Category = "DataAsset")
	int32 SlotNum;
	UPROPERTY(VisibleAnywhere, Category = "DataAsset")
	FName HandSocket;
	UPROPERTY(VisibleAnywhere, Category = "DataAsset")
	FName CarrySocket;
	UPROPERTY(VisibleAnywhere, Category = "DataAsset")
	bool bCanBeCarried;

};
