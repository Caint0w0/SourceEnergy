// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BagSaveData.h"
#include "Items/WarehouseManager.h"

UBagSaveData::UBagSaveData()
{
	
}

TArray<FMyItemInfo> UBagSaveData::GetItemsInBag()
{
	return ItemsInBag;
}
TArray<FMyItemInfo> UBagSaveData::GetArmorInBag()
{
	return Armor;
}

void UBagSaveData::SetItemsInBag(TArray<FMyItemInfo> InItems,TArray<FMyItemInfo> InArmor)
{
	ItemsInBag = InItems;
	Armor = InArmor;
}
