// Fill out your copyright notice in the Description page of Project Settings.


#include "StrengthenSystem/StrengthenInfoSave.h"

TArray<FStrengthenCellInfo> UStrengthenInfoSave::GetStrengthenTreeInfo()
{
	return StrengthenTreeInfo;
}
void UStrengthenInfoSave::SetStrengthenTreeInfo(TArray<FStrengthenCellInfo> InStrengthenTreeInfo)
{
	StrengthenTreeInfo = InStrengthenTreeInfo;
}
