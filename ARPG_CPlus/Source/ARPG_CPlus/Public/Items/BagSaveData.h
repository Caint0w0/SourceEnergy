// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BagSaveData.generated.h"

struct FMyItemInfo;
/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UBagSaveData : public USaveGame
{
	GENERATED_BODY()
public:
	UBagSaveData();
	UFUNCTION(BlueprintCallable)
	TArray<FMyItemInfo> GetItemsInBag();
	UFUNCTION(BlueprintCallable)
	TArray<FMyItemInfo> GetArmorInBag();
	UFUNCTION(BlueprintCallable)
	void SetItemsInBag(TArray<FMyItemInfo> InItems,TArray<FMyItemInfo> InArmor);
	
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FMyItemInfo> ItemsInBag;
	UPROPERTY(EditDefaultsOnly)
	TArray<FMyItemInfo> Armor;
};
