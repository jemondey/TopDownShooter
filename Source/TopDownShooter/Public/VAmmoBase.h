// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VAmmoBase.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AVAmmoBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVAmmoBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo Properties")
	float AmmoDamage;
	UPROPERTY(EditDefaultsOnly, Category = "Ammo Properties")
	float AmmoSpeed;

};
