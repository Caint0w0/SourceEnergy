// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/MySaveManager.h"

#include <string>

#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerData.h"
#include "UI/MyStartMenuUI.h"

UMySaveManager::UMySaveManager()
{
}

void UMySaveManager::SavePlayerData(UMyPlayerData* PlayerData, const FString& SlotName)
{
	if (!PlayerData)
	{
		PlayerData = NewObject<UMyPlayerData>();
		UE_LOG(LogTemp, Warning, TEXT("没有数据，新建了PlayerData"));
	}
	UGameplayStatics::SaveGameToSlot(PlayerData, SlotName, 0);
}

UMyPlayerData* UMySaveManager::LoadPlayerData(const FString& SlotName)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		return Cast<UMyPlayerData>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	}

	return nullptr;
}

FString UMySaveManager::NewGame()
{
	int i=1;
	FString Index = FString::FromInt(i);
	while(UGameplayStatics::DoesSaveGameExist(Index, 0))
	{
		i++;
		Index = FString::FromInt(i);
	}
	UMyPlayerData* NewPlayerData = NewObject<UMyPlayerData>();
	NewPlayerData->slotName=Index;
	SavePlayerData(NewPlayerData, Index);
	UE_LOG(LogTemp,Warning,TEXT("新建了游戏，Index为：%s"),*Index);
	return Index;
}
UMySaveManager::~UMySaveManager()
{
}
