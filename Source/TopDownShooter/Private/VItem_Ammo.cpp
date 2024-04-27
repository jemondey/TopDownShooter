// Fill out your copyright notice in the Description page of Project Settings.


#include "VItem_Ammo.h"
#include "VInventoryComponent.h"
#include "VGunBase.h"
#include "VCharacter.h"

void AVItem_Ammo::BeginPlay()
{
	Super::BeginPlay();

	UVInventoryComponent* InvComp = GetInstigator()->GetComponentByClass<UVInventoryComponent>();
	AVGunBase* GunActor = Cast<AVGunBase>(InvComp->FindActor(CompatibleGun));
	if (ensureAlways(GunActor))
	{
		GunActor->SetCarryAmmoAmount(Amount);
	}
	Destroy();
}