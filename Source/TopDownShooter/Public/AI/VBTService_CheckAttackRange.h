// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "VBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UVBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector WithinAttackRange;
	
};
