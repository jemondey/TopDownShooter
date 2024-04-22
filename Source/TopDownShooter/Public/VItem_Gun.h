// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VItemBase.h"
#include "VItem_Gun.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AVItem_Gun : public AVItemBase
{
	GENERATED_BODY()
	
public:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AVGunBase> GunClass;
	UPROPERTY(EditDefaultsOnly)
	FName AttachSocketName;
};
