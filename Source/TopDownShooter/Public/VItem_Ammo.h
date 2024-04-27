// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VItem_Ammo.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AVItem_Ammo : public AActor
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	TSubclassOf<AActor> CompatibleGun;
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 Amount;

};
