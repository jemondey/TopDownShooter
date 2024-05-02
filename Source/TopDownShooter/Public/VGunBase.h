// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VGameplayInterface.h"
#include "VGunBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAmmoChanged, AVGunBase*, GunClass, int32, CurrentAmmoAmount, int32, CarryAmmoAmount);


UCLASS()
class TOPDOWNSHOOTER_API AVGunBase : public AActor, public IVGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVGunBase();

	UPROPERTY(BlueprintAssignable)
	FOnAmmoChanged OnAmmoChanged;

	void PullTrigger(APawn* InstigatorPawn);
	void ReleaseTrigger(APawn* InstigatorPawn);
	void TryReload(APawn* InstigatorPawn);

	void SetCarryAmmoAmount(int32 Amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	void Shoot();
	void Reload();
	
	FTimerHandle ShootHandle;
	FTimerHandle ReloadHandle;

	AActor* InstigatorActor;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Gun Properties")
	TSubclassOf<AActor> AmmoClass;
	UPROPERTY(EditDefaultsOnly, Category = "Gun Properties")
	float FireRate;
	UPROPERTY(EditDefaultsOnly, Category = "Gun Properties")
	float ReloadTime;
	UPROPERTY(EditDefaultsOnly, Category = "Gun Properties")
	int32 MaxAmmoAmount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Properties")
	int32 CurrentAmmoAmount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Properties")
	int32 CarryAmmoAmount;
	UPROPERTY(EditAnywhere, Category = "Gun Properties")
	bool bIsAutoFire;
	bool bCanShoot;

};
