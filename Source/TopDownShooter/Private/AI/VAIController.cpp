// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AVAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}