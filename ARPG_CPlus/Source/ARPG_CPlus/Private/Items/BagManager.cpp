// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BagManager.h"

#include "Items/BagSaveData.h"
#include "Items/WarehouseManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBagManager::UBagManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	UBagManager::LoadData();
	Items.SetNum(MaxCellCntLimit);
	Armor.SetNum(3);
	ItemLocation=EMyItemLocation::Bag;
	for(auto& Item:Items)
	{
		Item.ItemLocation=EMyItemLocation::Bag;
	}
	for(auto& Item:Armor)
	{
		Item.ItemLocation=EMyItemLocation::Armed;
	}
	UBagManager::SaveData();
}

// Called when the game starts
void UBagManager::BeginPlay()
{
	Super::BeginPlay();
	LoadData();
}


// Called every frame
void UBagManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBagManager::SaveData()
{
	if (UBagSaveData* Save = Cast<UBagSaveData>(UGameplayStatics::CreateSaveGameObject(UBagSaveData::StaticClass())))
	{
		Save->SetItemsInBag(Items,Armor);
		if (UGameplayStatics::SaveGameToSlot(Save, FString("BagSaveData"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("UBagManager-->Save Success"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UBagManager-->Save Failed"));
		}
	}
}

void UBagManager::LoadData()
{
	if(UGameplayStatics::DoesSaveGameExist(FString("BagSaveData"),0))
	{
		UBagSaveData* save=Cast<UBagSaveData>(UGameplayStatics::LoadGameFromSlot(FString("BagSaveData"), 0));
		Items=save->GetItemsInBag();
		Armor=save->GetArmorInBag();
		UE_LOG(LogTemp,Warning,TEXT("UBagManager-->Loaded Success"));
	}else
	{
		UBagManager::SaveData();
		UE_LOG(LogTemp,Warning,TEXT("UBagManager-->Loaded Fail"));
	}
}

void UBagManager::LogMes()const
{
	UE_LOG(LogTemp, Warning, TEXT("BagManager::LogMes-->Start,Num==%d"),Items.Num());
	for(const auto& BagItem : Items)
	{
		UE_LOG(LogTemp, Warning, TEXT("ID==%d CurrentOwnedCnt==%d DisplayName==%s ItemLocation==%d ItemType==%d"),
			BagItem.ItemId,
			(int)BagItem.CurrentOwnedCnt,
			*BagItem.DisplayName,
			BagItem.ItemLocation,
			BagItem.ItemType);
	}
}

bool UBagManager::AddItemByArrayWithSave(const TArray<FMyItemInfo> ItemsToAdd)
{
	const bool IsAddSuccess=AddItemByArray(ItemsToAdd);
	SaveData();
	UE_LOG(LogTemp,Warning,TEXT("UBagManager::AddItemByArrayWithSave"));
	return IsAddSuccess;
}

bool UBagManager::AddItemWithSave(FMyItemInfo& ItemToAdd)
{
	const bool IsAddSuccess=AddItem(ItemToAdd);
	SaveData();
	return IsAddSuccess;
}


bool UBagManager::RemoveItemWithSave(const int ItemId,const int SubCnt)
{
	bool bIsRemoveSuccess=RemoveItem(ItemId,SubCnt);
	SaveData();
	return bIsRemoveSuccess;
}


bool UBagManager::JudgeCanArm(const FMyItemInfo Item,const int ArmArrayIndex)const
{
	if(!(Item.ItemType==EMyItemType::Arm||Item.ItemType==EMyItemType::Accessory||Item.ItemType==EMyItemType::Weapon))return false;
	if(Item.ItemType==EMyItemType::Arm)
	{
		if(Item.ArmType==EMyArmType::Helmet&&ArmArrayIndex==0)return true;
		if(Item.ArmType==EMyArmType::Chestplate&&ArmArrayIndex==1)return true;
		if(Item.ArmType==EMyArmType::Boots&&ArmArrayIndex==2)return true;
	}
	//TO//DO:完善所有条件判断 
	return false;
}

