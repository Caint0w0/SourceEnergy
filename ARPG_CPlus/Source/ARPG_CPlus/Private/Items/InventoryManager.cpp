// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InventoryManager.h"
#include "Engine/DataTable.h"
#include "Items/BagManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayer.h"
// Sets default values for this component's properties
UInventoryManager::UInventoryManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("DataTable'/Game/Data/DataTable/RecipeDataTable.RecipeDataTable'"));
	if (DataTableAsset.Succeeded())
	{
		RecipeDataTable = DataTableAsset.Object;
		//FRecipeRow temp=GetRecipeRowById(1);
		//UE_LOG(LogTemp,Warning,TEXT("RecipeId==%d,RequiredMaterials.Num()==%d"),temp.RecipeId,temp.RequiredMaterials.Num());
	}
	
	// ...
}


// Called when the game starts
void UInventoryManager::BeginPlay()
{
	Super::BeginPlay();
	AMyPlayer* PlayerRef=Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	BagManager=PlayerRef->BagManager;
	//const FRecipeRow Recipe = GetRecipeById(RecipeId);
	// ...
}


// Called every frame
void UInventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FRecipeRow UInventoryManager::GetRecipeRowById(int RecipeId)
{
	// 获取DataTable的所有行
	TArray<FName> RowNames= RecipeDataTable->GetRowNames();

	// 遍历每一行
	for (const auto& RowName : RowNames)
	{
		FRecipeRow* RowData = RecipeDataTable->FindRow<FRecipeRow>(RowName,FString(""),true);

		if (RowData->RecipeId == RecipeId)
		{
			return *RowData;
		}
	}
	return FRecipeRow();
}

bool UInventoryManager::CraftItem(int RecipeId)
{
	UE_LOG(LogTemp,Warning,TEXT("CraftItemBegin"));
	FRecipeRow Recipe = GetRecipeRowById(RecipeId);
	if (Recipe.RecipeId==0) return false;
	if(!BagManager)return false;
	//WarehouseManager->LogMes();
	bool bCanCraft=true;

	for (const FMyItemInfo& Material : Recipe.RequiredMaterials)
	{
		UE_LOG(LogTemp,Warning,TEXT("Recipe.RequiredMaterials Itemid==%d ItemCnt==%d"),Material.ItemId,Material.CurrentOwnedCnt);
		if (BagManager->CheckIsEnough(Material.ItemId, Material.CurrentOwnedCnt))
		{
			UE_LOG(LogTemp,Warning,TEXT("Enough"));
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Not Enough"));
			bCanCraft=false;break; // 某种材料不足，合成失败
		}
	}
	if(bCanCraft)
	{
		UE_LOG(LogTemp,Warning,TEXT("BagManager->GetAvailableSpace()==%d"),BagManager->GetAvailableSpace());
		if(BagManager->GetAvailableSpace()>=1)
		{
			for (const FMyItemInfo& Material : Recipe.RequiredMaterials)
			{
				bool Success=BagManager->RemoveItemWithSave(Material.ItemId, Material.CurrentOwnedCnt);
				UE_LOG(LogTemp,Warning,TEXT("BagManager->RemoveItemWithSave==%d"),Success);
			}
			BagManager->AddItem(Recipe.ResultItem);
			BagManager->SaveData();
			BagManager->LogMes();
			UE_LOG(LogTemp,Warning,TEXT("CraftItemSuccess"));
			return true;
		}
		UE_LOG(LogTemp,Warning,TEXT("CraftItemFailed-->Space is Not Enough!"));
		return false;
	}
	UE_LOG(LogTemp,Warning,TEXT("CraftItemFailed"));
	return false;
}