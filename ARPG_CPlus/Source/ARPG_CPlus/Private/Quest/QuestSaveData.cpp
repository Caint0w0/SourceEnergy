// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestSaveData.h"
#include "Quest/QuestManagerComponent.h"


TArray<FQuestStructure>  UQuestSaveData::GetCurrentQuests()
{
	return CurrentQuests;
}

void UQuestSaveData::SetCurrentQuests(TArray<FQuestStructure>& Quests)
{
	CurrentQuests = Quests;
}


TArray<FQuestNodeData>  UQuestSaveData::GetCurrentQuestNodesData()
{
	return CurrentQuestNodesData;
}

void UQuestSaveData::SetCurrentQuestNodesData(TArray<FQuestNodeData>& QuestNodesData)
{
	CurrentQuestNodesData = QuestNodesData;
}


TArray<FQuestStructure>  UQuestSaveData::GetCompletedQuests()
{
	return CompletedQuests;
}

void UQuestSaveData::SetCompletedQuests(TArray<FQuestStructure>& Quests)
{
	CompletedQuests = Quests;
}

int UQuestSaveData::GetCurrentFollowQuestId()
{
	return CurrentFollowQuestId;
}

void UQuestSaveData::SetCurrentFollowQuestId(const int QuestId)
{
	CurrentFollowQuestId = QuestId;
}

