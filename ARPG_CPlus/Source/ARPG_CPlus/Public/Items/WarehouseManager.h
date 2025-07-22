// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemManageBaseComponent.h"
#include "Components/ActorComponent.h"
#include "Enum/My_Enum.h"
#include "WarehouseManager.generated.h"
class UGameplayAbility;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_CPLUS_API UWarehouseManager : public UItemManageBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWarehouseManager();
	
	//override
	virtual void SaveData()override;
	
	virtual void LoadData()override;
	
	virtual bool AddItemByArrayWithSave(const TArray<FMyItemInfo> ItemsToAdd)override;
	
	virtual bool AddItemWithSave(FMyItemInfo& ItemToAdd)override;
	
	virtual bool RemoveItemWithSave(const int ItemId,const int SubCnt)override;

	virtual void LogMes()const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
