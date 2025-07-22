// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WarehouseManager.h"

#include "Items/WareHouseItemData.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UWarehouseManager::UWarehouseManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	UWarehouseManager::LoadData();
	Items.SetNum(MaxCellCntLimit);
	ItemLocation=EMyItemLocation::WareHouse;
	for(auto& Item:Items)
	{
		Item.ItemLocation=EMyItemLocation::WareHouse;
	}
	UWarehouseManager::SaveData();
}


// Called when the game starts
void UWarehouseManager::BeginPlay()
{
	Super::BeginPlay();
	LoadData();
}


// Called every frame
void UWarehouseManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//LogMes();
	// ...
}

void UWarehouseManager::SaveData()
{
	UWareHouseItemData* Save = Cast<UWareHouseItemData>(UGameplayStatics::CreateSaveGameObject(UWareHouseItemData::StaticClass()));
	if (Save)
	{
		Save->SetItemsInWareHouse(Items);
		if (UGameplayStatics::SaveGameToSlot(Save, FString("WareHouseData"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("UWarehouseManager-->Save Success"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UWarehouseManager-->Save Failed"));
		}
	}
}
void UWarehouseManager::LoadData()
{
	UWareHouseItemData* Save=Cast<UWareHouseItemData>(UGameplayStatics::LoadGameFromSlot(FString("WareHouseData"), 0));
	if(Save)
	{
		Items=Save->GetItemsInWareHouse();
		
		UE_LOG(LogTemp,Warning,TEXT("Loaded Success"));
	}else
	{
		UE_LOG(LogTemp,Warning,TEXT("Loaded Fail"));
	}
}

void UWarehouseManager::LogMes()const
{
	UE_LOG(LogTemp, Warning, TEXT("WarehouseManager::LogMes,Num==%d"),Items.Num());
	for(int32 i = 0; i < Items.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("ID==%d CurrentOwnedCnt==%d DisplayName==%s"), Items[i].ItemId, (int32)Items[i].CurrentOwnedCnt,*Items[i].DisplayName);
	}
}

bool UWarehouseManager::AddItemByArrayWithSave(const TArray<FMyItemInfo> ItemsToAdd)
{
	const bool IsAddSuccess=AddItemByArray(ItemsToAdd);
	SaveData();
	return IsAddSuccess;
}

bool UWarehouseManager::AddItemWithSave(FMyItemInfo& ItemToAdd)
{
	const bool IsAddSuccess=AddItem(ItemToAdd);
	SaveData();
	return IsAddSuccess;
}


bool UWarehouseManager::RemoveItemWithSave(const int ItemId,const int SubCnt)
{
	bool bIsRemoveSuccess=RemoveItem(ItemId,SubCnt);
	SaveData();
	return bIsRemoveSuccess;
}






