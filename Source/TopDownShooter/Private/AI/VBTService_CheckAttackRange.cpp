// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UVBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (MyController)
			{
				APawn* MyPawn = MyController->GetPawn();
				if (MyPawn)
				{
					float Distance = FVector::Distance(TargetActor->GetActorLocation(), MyPawn->GetActorLocation());
					bool bWithinRange = Distance < 2000.f;
					bool bHasLOS = false;
					if (bWithinRange)
					{
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					}
					BlackboardComp->SetValueAsBool(WithinAttackRange.SelectedKeyName, (bWithinRange && bHasLOS));
				}
			}
		}
	}
}