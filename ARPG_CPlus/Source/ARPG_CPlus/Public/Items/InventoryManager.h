// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WareHouseManager.h"
#include "Components/ActorComponent.h"
#include "InventoryManager.generated.h"


class UBagManager;

USTRUCT(BlueprintType)
struct FRecipeRow : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RecipeId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMyItemInfo> RequiredMaterials;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMyItemInfo ResultItem;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_CPLUS_API UInventoryManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryManager();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recipe")
	UDataTable* RecipeDataTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Recipe")
	UWarehouseManager* WarehouseManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Recipe")
	UBagManager* BagManager;
	UFUNCTION(BlueprintCallable)
	FRecipeRow GetRecipeRowById(int RecipeId);
	UFUNCTION(BlueprintCallable)
	bool CraftItem(int RecipeId);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
