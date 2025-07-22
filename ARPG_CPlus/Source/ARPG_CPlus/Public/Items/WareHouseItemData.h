// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WareHouseItemData.generated.h"

struct FMyItemInfo;
/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UWareHouseItemData : public USaveGame
{
	GENERATED_BODY()
public:
	UWareHouseItemData();
	UFUNCTION(BlueprintCallable)
	TArray<FMyItemInfo> GetItemsInWareHouse();
	UFUNCTION(BlueprintCallable)
	void SetItemsInWareHouse(TArray<FMyItemInfo> InItems);
	
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FMyItemInfo> ItemsInWareHouse;
};
