#pragma once

#include "CoreMinimal.h"
#include "MySaveManager.generated.h"

class UMyPlayerData;


UCLASS() 
class ARPG_CPLUS_API UMySaveManager: public UObject
{
	GENERATED_BODY() 
public:
	UMySaveManager();
	~UMySaveManager();
	static FString NewGame();
	static void SavePlayerData(UMyPlayerData* PlayerData, const FString& SlotName);
	static UMyPlayerData* LoadPlayerData(const FString& SlotName);
};
#pragma once


