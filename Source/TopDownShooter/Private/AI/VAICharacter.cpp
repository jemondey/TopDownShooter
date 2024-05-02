// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "BrainComponent.h"
#include "VAttributesComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AVAICharacter::AVAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("SensingComponent");
	AttributeComp = CreateDefaultSubobject<UVAttributesComponent>("AttributeComponent");
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>("GunMesh");
	GunMesh->SetupAttachment(GetMesh());

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void AVAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AVAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &AVAICharacter::OnHealthChanged);
}

void AVAICharacter::SetTargetActor(AActor* TargetActor)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", TargetActor);
	}
}

AActor* AVAICharacter::GetTargetActor()
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	}

	return nullptr;
}

UStaticMeshComponent* AVAICharacter::GetGunMesh()
{
	if (GunMesh)
	{
		return GunMesh;
	}
	return nullptr;
}

void AVAICharacter::OnPawnSeen(APawn* Pawn)
{
	if (GetTargetActor() != Pawn)
	{
		SetTargetActor(Pawn);
	}
}

void AVAICharacter::OnHealthChanged(AActor* InstigatorActor, UVAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta <= 0.0f)
	{
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		if (NewHealth <= 0.0f)
		{
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Died");
			}
			Destroy();
		}
	}
}