// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QuestSaveData.generated.h"

struct FQuestNodeData;
struct FQuestStructure;
/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UQuestSaveData : public USaveGame
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<FQuestStructure> CurrentQuests{};
	
	UPROPERTY()
	TArray<FQuestNodeData> CurrentQuestNodesData{};
	
	UPROPERTY()
	TArray<FQuestStructure> CompletedQuests{};

	UPROPERTY()
	int CurrentFollowQuestId;
public:
	//GetterAndSetter
	UFUNCTION(BlueprintCallable)
	TArray<FQuestStructure>  GetCurrentQuests();
	UFUNCTION(BlueprintCallable)
	void SetCurrentQuests(TArray<FQuestStructure>& Quests);

	UFUNCTION(BlueprintCallable)
	TArray<FQuestNodeData>  GetCurrentQuestNodesData();
	UFUNCTION(BlueprintCallable)
	void SetCurrentQuestNodesData(TArray<FQuestNodeData>& QuestNodesData);

	UFUNCTION(BlueprintCallable)
	TArray<FQuestStructure>  GetCompletedQuests();
	UFUNCTION(BlueprintCallable)
	void SetCompletedQuests(TArray<FQuestStructure>& Quests);

	UFUNCTION(BlueprintCallable)
	int  GetCurrentFollowQuestId();
	UFUNCTION(BlueprintCallable)
	void SetCurrentFollowQuestId(const int QuestId);
};
