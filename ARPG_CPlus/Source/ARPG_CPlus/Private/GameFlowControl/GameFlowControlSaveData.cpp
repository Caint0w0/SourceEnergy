// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFlowControl/GameFlowControlSaveData.h"

TArray<bool> UGameFlowControlSaveData::GetGameFlowKeyPoints()
{
	return GameFlowKeyPoints;
}

void UGameFlowControlSaveData::SetGameFlowKeyPoints(TArray<bool> InGameFlowKeyPoints)
{
	GameFlowKeyPoints = InGameFlowKeyPoints;
}


bool UGameFlowControlSaveData::GetIsFirstInGame()
{
	return bIsFirstInGame;
}

void UGameFlowControlSaveData::SetIsFirstInGame(bool Value)
{
	bIsFirstInGame = Value;
}
