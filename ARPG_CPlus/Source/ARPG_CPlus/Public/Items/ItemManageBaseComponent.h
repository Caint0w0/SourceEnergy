// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/My_Enum.h"
#include "ItemManageBaseComponent.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FMyItemInfo
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int64 CurrentOwnedCnt;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMyItemType ItemType{EMyItemType::Item};
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMyArmType ArmType{EMyArmType::None};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMyItemLocation ItemLocation{EMyItemLocation::None};
	
	FMyItemInfo(int32 ItemId,int64 CurrentOwnedCnt,FString DisplayName) : ItemId(ItemId), CurrentOwnedCnt(CurrentOwnedCnt), DisplayName(DisplayName)
	{}
	FMyItemInfo()
	{
		ItemId = 0;
		CurrentOwnedCnt=0;
		DisplayName=FString("Default");
	}
};

USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FMyItemData:public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxOwnedCnt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemBaseName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;
};

USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FAttributeModifier
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AttributeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PercentValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AddedValue;
};

USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FAttrModItemData:public FMyItemData
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAttributeModifier> AttributeMods;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayAbility>> GAsToAdd;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_CPLUS_API UItemManageBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemManageBaseComponent();
	
	UItemManageBaseComponent(int MaxCellCntLimit,EMyItemLocation ItemLocation):
	MaxCellCntLimit(MaxCellCntLimit),
	ItemLocation(ItemLocation)
	{
		PrimaryComponentTick.bCanEverTick = true;
		
		static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("DataTable'/Game/Data/DataTable/ItemsData.ItemsData'"));
		if (DataTableAsset.Succeeded())
		{
			ItemDataTable = DataTableAsset.Object;
		}
	}
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveData();
	
	UFUNCTION(BlueprintCallable)
	virtual void LoadData();

	UFUNCTION(BlueprintCallable)
	virtual bool AddItemByArrayWithSave(const TArray<FMyItemInfo> ItemsToAdd);
	
	UFUNCTION(BlueprintCallable)
	virtual bool AddItemWithSave(FMyItemInfo& ItemToAdd);

	UFUNCTION(BlueprintCallable)
	virtual bool RemoveItemWithSave(const int ItemId,const int SubCnt);
	
	UFUNCTION(BlueprintCallable)
	virtual bool AddItemByArray(TArray<FMyItemInfo> ItemsToAdd);
	
	UFUNCTION(BlueprintCallable)
	virtual bool AddItem(FMyItemInfo& ItemToAdd);

	UFUNCTION(BlueprintCallable)
	virtual int GetAvailableSpace()const;

	UFUNCTION(BlueprintCallable)
	virtual bool RemoveItem(const int ItemId,const int SubCnt);

	UFUNCTION(BlueprintCallable)
	virtual void LogMes()const;
	
	UFUNCTION(BlueprintCallable)
	virtual FMyItemInfo GetItemInfoByItemId(const int ItemId);

	static UDataTable* ItemDataTable;
	UFUNCTION(BlueprintCallable)
	static FMyItemData GetItemDataByItemId(const int ItemId);

	UFUNCTION(BlueprintCallable)
	virtual bool CheckIsEnough(const int ItemId,const int Cnt)const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	TArray<FMyItemInfo> Items;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	int MaxCellCntLimit{25};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	EMyItemLocation ItemLocation{EMyItemLocation::None};
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
