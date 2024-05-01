// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VAICharacter.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AVAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVAICharacter();

	virtual void PostInitializeComponents() override;

	UStaticMeshComponent* GetGunMesh();

protected:

	//UPROPERTY(EditDefaultsOnly, Category = "UI")
	//TSubclassOf<UUserWidget> HealthBarWidgetClass;

	//class USWorldUserWidget* ActiveHealthBar;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPawnSensingComponent* PawnSensingComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UVAttributesComponent* AttributeComp;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GunMesh;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UVAttributesComponent* OwningComp, float NewHealth, float Delta);

	void SetTargetActor(AActor* TargetActor);
	AActor* GetTargetActor();

};
