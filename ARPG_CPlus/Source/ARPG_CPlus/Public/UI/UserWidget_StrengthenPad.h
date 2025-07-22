// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MyUserWidgetBase.h"
#include "UserWidget_StrengthenPad.generated.h"

class UBagManager;
class UWarehouseManager;
struct FStrengthenCellInfo;
class UStrengthenManager;
class AMyPlayer;
/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UUserWidget_StrengthenPad : public UMyUserWidgetBase
{
	GENERATED_BODY()
public:
	UUserWidget_StrengthenPad();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strengthen")
	int SelectedIndex=-1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strengthen")
	UBagManager* WarehouseManager;
	UFUNCTION(BlueprintCallable, Category = "Strengthen")
	bool TryStrengthenByCellIndex(int index);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStrengthenManager* StrengthenManager;
	UFUNCTION(BlueprintCallable)
	FStrengthenCellInfo GetStrengthenCellInfoInterface(int index);
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
    FSavedAttributes TempSavedAttributes;
	AMyPlayer* MyPlayer;
	UFUNCTION(BlueprintCallable)
	void GetSavedAttributesData();
	UFUNCTION(BlueprintCallable)
	void StrengthenByName(FString AttributeName,float value);
	UFUNCTION(BlueprintCallable)
	float GetAttributeByName(FString AttributeName);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePadInfo();
	UFUNCTION(BlueprintCallable)
	void SaveToSlot();
};
