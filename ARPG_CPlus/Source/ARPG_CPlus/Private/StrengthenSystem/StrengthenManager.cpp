// Fill out your copyright notice in the Description page of Project Settings.


#include "StrengthenSystem/StrengthenManager.h"

#include "Kismet/GameplayStatics.h"
#include "StrengthenSystem/StrengthenInfoSave.h"
UStrengthenManager::UStrengthenManager()
{
	bool bIsExist=UGameplayStatics::DoesSaveGameExist(FString("StrengthenInfo"), 0);
	if(bIsExist)
	{
		Load();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("New StrengthenInfo"));
		FStrengthenCellInfo SCI_1=FStrengthenCellInfo();
		SCI_1.bIsActive = false;
		SCI_1.DescriptionText=FString("BaseAttack+10");
		TArray<FMyItemInfo>NeededItems;
		NeededItems.Add(FMyItemInfo(1,10,FString("源能结晶")));
		SCI_1.NeededItems=NeededItems;
		SCI_1.PreIndex=TArray<int32>();
		StrengthenTree_1.Add(SCI_1);


		SCI_1.bIsActive = false;
		SCI_1.DescriptionText=FString("MaxHealth+100");
		NeededItems.Empty();
		NeededItems.Add(FMyItemInfo(1,15,FString("源能结晶")));
		SCI_1.NeededItems=NeededItems;
		SCI_1.PreIndex={0};
		StrengthenTree_1.Add(SCI_1);

		SCI_1.bIsActive = false;
		SCI_1.DescriptionText=FString("BaseResistance+10");
		NeededItems.Empty();
		NeededItems.Add(FMyItemInfo(1,15,FString("源能结晶")));
		SCI_1.NeededItems=NeededItems;
		SCI_1.PreIndex={0};
		StrengthenTree_1.Add(SCI_1);
		Save();
	}
}

UStrengthenManager::~UStrengthenManager()
{
	
}
void UStrengthenManager::Save()
{
	UStrengthenInfoSave* SaveData=Cast<UStrengthenInfoSave>(UGameplayStatics::CreateSaveGameObject(UStrengthenInfoSave::StaticClass()));
    SaveData->SetStrengthenTreeInfo(StrengthenTree_1);
	UE_LOG(LogTemp, Warning, TEXT("In Save() :SaveData->GetStrengthenTreeInfo().Num()==%d"),SaveData->GetStrengthenTreeInfo().Num());
	UGameplayStatics::SaveGameToSlot(SaveData,FString("StrengthenInfo"), 0);
	UE_LOG(LogTemp, Warning, TEXT("UStrengthenManager::Save Success"));
}

void UStrengthenManager::Load()
{
	UStrengthenInfoSave* SaveData=Cast<UStrengthenInfoSave>(UGameplayStatics::LoadGameFromSlot(FString("StrengthenInfo"), 0));
	StrengthenTree_1=SaveData->GetStrengthenTreeInfo();
}
FStrengthenCellInfo UStrengthenManager::GetStrengthenCellInfo(int index)
{
	if(index>=0&&index<StrengthenTree_1.Num())
	{
		return StrengthenTree_1[index];
	}
	return FStrengthenCellInfo();
}

bool UStrengthenManager::CheckPreAllIsActive(int index)
{
	TArray<int> AllPreIndex=StrengthenTree_1[index].PreIndex;
	for(int i=0;i<AllPreIndex.Num();i++)
	{
		if(AllPreIndex[i]>=0&&AllPreIndex[i]<StrengthenTree_1.Num())
		{
			if(!StrengthenTree_1[AllPreIndex[i]].bIsActive)
			{
				return false;
			}
		}
	}
	return true;
}

void UStrengthenManager::SetCellIsActiveByIndex(int index,bool isActive)
{
	if(index>=0&&index<StrengthenTree_1.Num())
	{
		StrengthenTree_1[index].bIsActive=isActive;
	}
}
