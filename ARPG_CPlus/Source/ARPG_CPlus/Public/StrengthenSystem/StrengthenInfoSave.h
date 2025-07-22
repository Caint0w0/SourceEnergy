// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Items/WarehouseManager.h"
#include "StrengthenInfoSave.generated.h"

USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FStrengthenCellInfo
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int32> PreIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DescriptionText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FMyItemInfo> NeededItems;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsActive=false;
	FStrengthenCellInfo()
	{
		PreIndex=TArray<int32>();
		NeededItems=TArray<FMyItemInfo>();
		DescriptionText = FString("Default");
		bIsActive=false;
	}
};
/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UStrengthenInfoSave : public USaveGame
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<FStrengthenCellInfo> StrengthenTreeInfo;
public:
	UFUNCTION(BlueprintCallable)
	TArray<FStrengthenCellInfo> GetStrengthenTreeInfo();
	UFUNCTION(BlueprintCallable)
	void SetStrengthenTreeInfo(TArray<FStrengthenCellInfo> InStrengthenTreeInfo);
};
