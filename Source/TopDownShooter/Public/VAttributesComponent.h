// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VAttributesComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UVAttributesComponent*, OwningComp, float, NewHealth, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UVAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UVAttributesComponent();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	static UVAttributesComponent* GetAttributes(AActor* FromActor);
	static bool IsActorAlive(AActor* Actor);
	bool IsAlive();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attributes")
	float Health;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attributes")
	float HealthMax;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ApplyHealthChange(AActor* InstigatorActor, float Delta);
};
