// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameFlowControlSaveData.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UGameFlowControlSaveData : public USaveGame
{
	GENERATED_BODY()
private:
	UPROPERTY()
	bool bIsFirstInGame{true};
	
	UPROPERTY()
	TArray<bool> GameFlowKeyPoints{false};
public:
	UFUNCTION(BlueprintCallable,Category="GameFlowControl")
	TArray<bool> GetGameFlowKeyPoints();
	UFUNCTION(BlueprintCallable,Category="GameFlowControl")
	void SetGameFlowKeyPoints(TArray<bool> InGameFlowKeyPoints);

	UFUNCTION(BlueprintCallable,Category="GameFlowControl")
	bool GetIsFirstInGame();
	UFUNCTION(BlueprintCallable,Category="GameFlowControl")
	void SetIsFirstInGame(bool Value);
};
