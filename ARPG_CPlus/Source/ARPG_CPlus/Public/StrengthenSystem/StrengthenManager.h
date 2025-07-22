// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "StrengthenManager.generated.h"
struct FStrengthenCellInfo;
/**
 * 
 */
class UStrengthenInfoSave;
UCLASS()
class ARPG_CPLUS_API UStrengthenManager: public UObject
{
	GENERATED_BODY()
public:
	UStrengthenManager();
	~UStrengthenManager();
	UPROPERTY(EditDefaultsOnly)
	TArray<FStrengthenCellInfo> StrengthenTree_1;

	UFUNCTION(BlueprintCallable)
	void Save();
	UFUNCTION(BlueprintCallable)
	void Load();
	UFUNCTION(BlueprintCallable)
	FStrengthenCellInfo GetStrengthenCellInfo(int index);
	UFUNCTION(BlueprintCallable)
	bool CheckPreAllIsActive(int index);
	UFUNCTION(BlueprintCallable)
	void SetCellIsActiveByIndex(int index,bool isActive);
};
