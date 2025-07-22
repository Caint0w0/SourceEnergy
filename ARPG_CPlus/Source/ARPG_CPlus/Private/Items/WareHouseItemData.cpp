// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WareHouseItemData.h"
#include "Items/WarehouseManager.h"
UWareHouseItemData::UWareHouseItemData()
{

}
TArray<FMyItemInfo> UWareHouseItemData::GetItemsInWareHouse()
{
	return ItemsInWareHouse;
}
void UWareHouseItemData::SetItemsInWareHouse(TArray<FMyItemInfo> InItems)
{
	ItemsInWareHouse = InItems;
}


