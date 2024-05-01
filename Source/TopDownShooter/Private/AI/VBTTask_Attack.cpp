// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VBTTask_Attack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "VAttributesComponent.h"
#include "AI/VAICharacter.h"

UVBTTask_Attack::UVBTTask_Attack()
{
	MaxBulletSpread = 2.0f;
}

EBTNodeResult::Type UVBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		AVAICharacter* MyPawn = Cast<AVAICharacter>(AIController->GetPawn());
		if (!MyPawn)
		{
			return EBTNodeResult::Failed;
		}
		//FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Fire_Socket");
		FVector MuzzleLocation = MyPawn->GetGunMesh()->GetSocketLocation("Fire_Socket");

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (!TargetActor)
		{
			return EBTNodeResult::Failed;
		}

		if (!UVAttributesComponent::IsActorAlive(TargetActor))
		{
			return EBTNodeResult::Failed;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = MyPawn;

		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();
		MuzzleRotation.Pitch += FMath::RandRange(0.0f, MaxBulletSpread);
		MuzzleRotation.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);

		AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
		NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}