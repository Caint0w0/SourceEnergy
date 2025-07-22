// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemManageBaseComponent.h"
#include "Components/ActorComponent.h"
#include "BagManager.generated.h"


struct FMyItemInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_CPLUS_API UBagManager : public UItemManageBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBagManager();
	//override
	virtual void SaveData()override;
	
	virtual void LoadData()override;
	
	virtual bool AddItemByArrayWithSave(const TArray<FMyItemInfo> ItemsToAdd)override;
	
	virtual bool AddItemWithSave(FMyItemInfo& ItemToAdd)override;
	
	virtual bool RemoveItemWithSave(const int ItemId,const int SubCnt)override;
	
	virtual void LogMes()const override;
	//

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BagItemData")
	TArray<FMyItemInfo> Armor{};
	
	UFUNCTION(BlueprintCallable)
	bool JudgeCanArm(const FMyItemInfo Item,const int ArmArrayIndex)const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
