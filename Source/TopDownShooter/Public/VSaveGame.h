// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VSaveGame.generated.h"


class AVItemBase;
class AVAICharacter;
class AVCharacter;
class AAIController;


UCLASS()
class TOPDOWNSHOOTER_API UVSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameSave")
	AVCharacter* PlayerCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
	FTransform PlayerPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameSave")
	TArray<AVAICharacter*> EnemyCharacterArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameSave")
	TArray<AAIController*> EnemyControllerArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameSave")
	TArray<FTransform> EnemyPositionArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameSave")
	TArray<AVItemBase*> ItemBaseArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameSave")
	TArray<FTransform> ItemPositionArray;
};
