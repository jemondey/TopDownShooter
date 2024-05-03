// Fill out your copyright notice in the Description page of Project Settings.


#include "VGameInstance.h"
#include "VSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "VCharacter.h"
#include "AI/VAICharacter.h"
#include "VItemBase.h"
#include "VAttributesComponent.h"

void UVGameInstance::SaveGame()
{
	UVSaveGame* SaveGameInstance = Cast<UVSaveGame>(UGameplayStatics::CreateSaveGameObject(UVSaveGame::StaticClass()));
	if (!SaveGameInstance)
	{
		return;
	}

	AVCharacter* Character = Cast<AVCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Character)
	{
		SaveGameInstance->PlayerCharacter = Character;
		SaveGameInstance->PlayerPosition = Character->GetActorTransform();
	}
	TArray<AActor*> EnemyActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVAICharacter::StaticClass(), EnemyActorArray);
	if (!EnemyActorArray.IsEmpty())
	{
		for (AActor* ActorInArray : EnemyActorArray)
		{
			if(ActorInArray)
			{
				SaveGameInstance->EnemyCharacterArray.Add(Cast<AVAICharacter>(ActorInArray));
				SaveGameInstance->EnemyPositionArray.Add(ActorInArray->GetTransform());
			}
		}
	}
	TArray<AActor*> ItemsActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVItemBase::StaticClass(), ItemsActorArray);
	if (!ItemsActorArray.IsEmpty())
	{
		for (AActor* ActorInArray : ItemsActorArray)
		{
			if (ActorInArray)
			{
				SaveGameInstance->ItemBaseArray.Add(Cast<AVItemBase>(ActorInArray));
				SaveGameInstance->ItemPositionArray.Add(ActorInArray->GetTransform());
			}
		}
	}

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SaveSlot"), 0);
}

void UVGameInstance::LoadGame()
{
	UVSaveGame* LoadedSaveGame = Cast<UVSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot"), 0));
	if (!LoadedSaveGame)
	{
		return;
	}
	UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->SetActorTransform(LoadedSaveGame->PlayerPosition);
	for(int32 index = 0; index <= LoadedSaveGame->EnemyCharacterArray.Num() - 1; index++)
	{
		AVAICharacter* EnemyCharacter = LoadedSaveGame->EnemyCharacterArray[index];
		FTransform EnemyTransform = LoadedSaveGame->EnemyPositionArray[index];
		if (EnemyCharacter && !UVAttributesComponent::IsActorAlive(EnemyCharacter))
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AVAICharacter* SpawnedEnemy = GetWorld()->SpawnActor<AVAICharacter>(EnemyCharacter->GetClass(), EnemyTransform, SpawnParams);
			SpawnedEnemy->SpawnDefaultController();
		}
		else if(EnemyCharacter)
		{
			EnemyCharacter->SetActorTransform(EnemyTransform);
		}
	}
}
