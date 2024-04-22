// Fill out your copyright notice in the Description page of Project Settings.


#include "VItem_Gun.h"
#include "VCharacter.h"
#include "VGunBase.h"

void AVItem_Gun::Interact_Implementation(APawn* InstigatorPawn)
{
	AActor* InstigatorActor = Cast<AActor>(InstigatorPawn);

	/*if (InstigatorPawn->Children.Num() >= 1)
	{
		AActor* KEK = Cast<AActor>(InstigatorActor->Children[0].GetClass());
		if (KEK)
		{
			KEK->Destroy();
		}
	}*/

	FVector Location = InstigatorActor->GetActorLocation();
	FRotator Rotation = InstigatorActor->GetActorRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = InstigatorPawn;
	SpawnParams.Owner = InstigatorPawn;

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(GunClass, Location, Rotation, SpawnParams);
	USceneComponent* AttachComponent = Cast<USceneComponent>(Cast<AVCharacter>(InstigatorActor)->GetMesh());
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepRelative,
		true);
	SpawnedActor->AttachToComponent(AttachComponent, AttachmentRules, AttachSocketName);
	AVCharacter* CH = Cast<AVCharacter>(InstigatorPawn);
	CH->EquipedWeapon = GunClass;

}
