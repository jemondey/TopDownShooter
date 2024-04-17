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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
