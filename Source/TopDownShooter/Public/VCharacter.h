// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VCharacter.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AVCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVCharacter();

	FVector GetPointUnderCursor();
	FVector GetCameraLocation();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AVGunBase> EquipedWeapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	class UVInteractionComponent* InteractionComp;
	UPROPERTY(VisibleAnywhere)
	class UVAttributesComponent* AttributesComp;

	

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Aim();
	void RotatePlayer(FVector Direction);
	void Interact();
	void Attack();
	void StopAttack();
	void Reload();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	APlayerController* PlayerController;

};
