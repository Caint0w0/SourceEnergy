// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemManageBaseComponent.h"

// 定义静态成员变量
UDataTable* UItemManageBaseComponent::ItemDataTable = nullptr;

// Sets default values for this component's properties
UItemManageBaseComponent::UItemManageBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	//初始化为指定长度
	//Items.SetNum(MaxCellCntLimit);在LoadData之后,And MaxCellCntLimit  has been not Added to SaveData
	
	//读取ItemData
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("DataTable'/Game/Data/DataTable/ItemsData.ItemsData'"));
	if (DataTableAsset.Succeeded())
	{
		ItemDataTable = DataTableAsset.Object;
	}
	// ...
}



// Called when the game starts
void UItemManageBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemManageBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItemManageBaseComponent::SaveData()
{
	UE_LOG(LogTemp,Warning,TEXT("UItemManageBaseComponent::SaveData"));
}

void UItemManageBaseComponent::LoadData()
{
	UE_LOG(LogTemp,Warning,TEXT("UItemManageBaseComponent::LoadData"));
}

bool UItemManageBaseComponent::AddItem(FMyItemInfo& ItemToAdd)
{
	//基础版本只实现添加，不更改数据
	for(auto& Item : Items)
	{
		if(Item.ItemId == ItemToAdd.ItemId)
		{
			Item.CurrentOwnedCnt += ItemToAdd.CurrentOwnedCnt;
			return true;
		}
	}
	if(GetAvailableSpace())
	{
		for(auto& Item : Items)
		{
			if(Item.ItemId == 0)
			{
				ItemToAdd.ItemLocation = ItemLocation;
				Item=ItemToAdd;
				return true;
			}
		}
	}
	return false;
}

bool UItemManageBaseComponent::AddItemByArray(TArray<FMyItemInfo> ItemsToAdd)
{
	int NeededSpace = ItemsToAdd.Num();
	for(auto& AddItem : ItemsToAdd)
	{
		for(const auto& Item : Items)
		{
			if(AddItem.ItemId == Item.ItemId)
			{
				NeededSpace --;
				break;
			}
		}
	}
	if(NeededSpace>GetAvailableSpace())return false;

	for(auto& Item : ItemsToAdd)
	{
		AddItem(Item);
	}
	return true;
}

int UItemManageBaseComponent::GetAvailableSpace()const
{
	int AvailableSpace=0;
	const int LoopLimit=FMath::Min(MaxCellCntLimit,Items.Num());
	for(int Index = 0; Index < LoopLimit; Index++)
	{
		if(Items[Index].ItemId==0)
		{
			AvailableSpace++;
		}
	}
	return AvailableSpace;
}

bool UItemManageBaseComponent::RemoveItem(const int ItemId,const int SubCnt)
{
	for(auto& Item : Items)
	{
		if(Item.ItemId == ItemId)
		{
			if(Item.CurrentOwnedCnt>SubCnt)
			{
				Item.CurrentOwnedCnt-=SubCnt;
				return true;//如果数量够的话就直接减
			}
			if(Item.CurrentOwnedCnt==SubCnt)
			{
				FMyItemInfo Temp=FMyItemInfo();
				Temp.ItemLocation=ItemLocation;
				Item=Temp;
				return true;
			}
			return false;
		}
	}
	return false;
}

FMyItemInfo UItemManageBaseComponent::GetItemInfoByItemId(const int ItemId)
{
	for(auto& Item : Items)
	{
		if(Item.ItemId == ItemId)
		{
			return Item;
		}
	}
	return FMyItemInfo();
}

bool UItemManageBaseComponent::CheckIsEnough(const int ItemId,const int Cnt)const
{
	for(const auto& Item : Items)
	{
		if(Item.ItemId == ItemId)
		{
			if(Item.CurrentOwnedCnt>=Cnt)
			{
				return true;
			}
				return false;
		}
	}
	return false;
}

FMyItemData UItemManageBaseComponent::GetItemDataByItemId(const int ItemId)
{
	if(!ItemDataTable)return FMyItemData();
	// 获取DataTable的所有行
	TArray<FName> RowNames= ItemDataTable->GetRowNames();

	// 遍历每一行
	for (const auto& RowName : RowNames)
	{
		FMyItemData* RowData = ItemDataTable->FindRow<FMyItemData>(RowName,FString(""),true);

		if (RowData->ItemId == ItemId)
		{
			return *RowData;
		}
	}
	return FMyItemData();
}

bool UItemManageBaseComponent::AddItemByArrayWithSave(const TArray<FMyItemInfo> ItemsToAdd)
{
	const bool IsAddSuccess=AddItemByArray(ItemsToAdd);
	SaveData();
	return IsAddSuccess;
}

bool UItemManageBaseComponent::AddItemWithSave(FMyItemInfo& ItemToAdd)
{
	const bool IsAddSuccess=AddItem(ItemToAdd);
	SaveData();
	return IsAddSuccess;
}


bool UItemManageBaseComponent::RemoveItemWithSave(const int ItemId,const int SubCnt)
{
	bool bIsRemoveSuccess=RemoveItem(ItemId,SubCnt);
	SaveData();
	return bIsRemoveSuccess;
}

void UItemManageBaseComponent::LogMes() const
{
	UE_LOG(LogTemp,Warning,TEXT("Error! Should not Call The Base Version of LogMes"));
}
