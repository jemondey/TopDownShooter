// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VItem_HealBox.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AVItem_HealBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVItem_HealBox();

	void Heal(AActor* ActorToHeal);
	void AddHeal();
	void ReduceHeal(AActor* ActorToHeal);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditDefaultsOnly, Category = "HealBox")
	float HealAmount;
	UPROPERTY(EditDefaultsOnly, Category = "HealBox")
	int32 AmountToGive;
	UPROPERTY(VisibleAnywhere, Category = "HealBox")
	int32 CurrentAmount;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
