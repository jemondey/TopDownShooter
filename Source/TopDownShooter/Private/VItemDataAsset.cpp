// Fill out your copyright notice in the Description page of Project Settings.


#include "VItemDataAsset.h"

FName UVItemDataAsset::GetHandSocketName()
{
    return HandSocket;
}

FName UVItemDataAsset::GetCarrySocketName()
{
    return CarrySocket;
}

bool UVItemDataAsset::GetCanBeCarried()
{
    return bCanBeCarried;
}
