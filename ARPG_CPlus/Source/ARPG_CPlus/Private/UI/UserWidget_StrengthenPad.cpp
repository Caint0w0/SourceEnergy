// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserWidget_StrengthenPad.h"

#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerData.h"
#include "Player/MyPlayer.h"
#include "Player/MyPlayerAttributeSet.h"
#include "Items/BagManager.h"
#include "StrengthenSystem/StrengthenManager.h"
#include "StrengthenSystem/StrengthenInfoSave.h"

UUserWidget_StrengthenPad::UUserWidget_StrengthenPad()
{
	
	//不要在这构造StrengthenManager，会出奇奇怪怪的bug
	//UE_LOG(LogTemp, Warning, TEXT("DescriptionText===%s"),*StrengthenManager->GetStrengthenCellInfo(0).DescriptionText);
	
}

void UUserWidget_StrengthenPad::GetSavedAttributesData()
{
	UMyPlayerData* LoadedPlayerData= Cast<UMyPlayerData>(UGameplayStatics::LoadGameFromSlot(FString("PlayerAttributes"), 0));
	TempSavedAttributes=LoadedPlayerData->GetSavedAttributes();
}

void UUserWidget_StrengthenPad::StrengthenByName(FString AttributeName,float value)
{
	if(AttributeName.Equals(FString("BaseAttack")))
	{
		TempSavedAttributes.BaseAttack=TempSavedAttributes.BaseAttack+value;
		UE_LOG(LogTemp,Warning,TEXT("UUserWidget_StrengthenPad::StrengthenByName-->BaseAttack==%f"),TempSavedAttributes.BaseAttack);
	}
	else if(AttributeName.Equals(FString("MaxHealth")))
	{
		TempSavedAttributes.MaxHealth+=value;
	}
	else if(AttributeName.Equals(FString("BaseResistance")))
	{
		TempSavedAttributes.BaseResistance+=value;
	}
	else if(AttributeName.Equals(FString("BaseStagger")))
	{
		TempSavedAttributes.BaseStagger+=value;
	}
	else if(AttributeName.Equals(FString("CRT")))
	{
		TempSavedAttributes.CRT+=value;
	}
	else if(AttributeName.Equals(FString("CriticalDamage")))
	{
		TempSavedAttributes.CriticalDamage+=value;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("UUserWidget_StrengthenPad::StrengthenByName-->其他参数"));
	}
	MyPlayer=Cast<AMyPlayer>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetPawn());
	if(MyPlayer!=nullptr)
	{
		Cast<UMyPlayerAttributeSet>(MyPlayer->GetAttributeSet())->InitPlayerAttributeSet(TempSavedAttributes);
		UE_LOG(LogTemp,Warning,TEXT("UUserWidget_StrengthenPad::StrengthenByName-->AS-->BaseAttack==%f"),Cast<UMyPlayerAttributeSet>(MyPlayer->GetAttributeSet())->BaseAttack.GetBaseValue());
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("UUserWidget_StrengthenPad::StrengthenByName-->MyPlayer is NULL"));
	}
	//测试先在这更新
	//UpdatePadInfo();
}

float UUserWidget_StrengthenPad::GetAttributeByName(FString AttributeName)
{
	UE_LOG(LogTemp,Warning,TEXT("GetAttributeByName-->Start"));
	if(AttributeName.Equals(FString("MaxHealth")))
	{
		return TempSavedAttributes.MaxHealth;
	}
	if(AttributeName.Equals(FString("BaseAttack")))
	{
		return TempSavedAttributes.BaseAttack;
	}
	if(AttributeName.Equals(FString("BaseResistance")))
	{
		return TempSavedAttributes.BaseResistance;
	}
	if(AttributeName.Equals(FString("BaseStagger")))
	{
		return TempSavedAttributes.BaseStagger;
	}
	if(AttributeName.Equals(FString("CRT")))
	{
		return TempSavedAttributes.CRT;
	}
	if(AttributeName.Equals(FString("CriticalDamage")))
	{
		return TempSavedAttributes.CriticalDamage;
	}
	UE_LOG(LogTemp,Warning,TEXT("GetAttributeByName-->NotFind"));
	return 0.f;
}
void UUserWidget_StrengthenPad::SaveToSlot()
{
	UMyPlayerData* LoadedPlayerData = Cast<UMyPlayerData>(UGameplayStatics::CreateSaveGameObject(UMyPlayerData::StaticClass()));
	LoadedPlayerData->SetSavedAttributes(TempSavedAttributes);
	UGameplayStatics::SaveGameToSlot(LoadedPlayerData, FString("PlayerAttributes"), 0);
}
FStrengthenCellInfo UUserWidget_StrengthenPad::GetStrengthenCellInfoInterface(int index)
{
	if(!StrengthenManager)StrengthenManager=NewObject<UStrengthenManager>();
	if(StrengthenManager!=nullptr)
	{
		return StrengthenManager->GetStrengthenCellInfo(index);
	}
	return FStrengthenCellInfo();
}
bool UUserWidget_StrengthenPad::TryStrengthenByCellIndex(int index)
{
	if(!WarehouseManager)
	{
		UE_LOG(LogTemp,Warning,TEXT("WarehouseManager ptr in UUserWidget_StrengthenPad is Not Valid"));
		return false;
	}
	if(!StrengthenManager)StrengthenManager=NewObject<UStrengthenManager>();
	
		FStrengthenCellInfo temp=StrengthenManager->GetStrengthenCellInfo(index);
		bool bCanStrengthen=true;
		for(int i=0;i<temp.NeededItems.Num();i++)
		{
			int OwnedCnt=WarehouseManager->GetItemInfoByItemId(temp.NeededItems[i].ItemId).CurrentOwnedCnt;
			if(temp.NeededItems[i].CurrentOwnedCnt>OwnedCnt||!StrengthenManager->CheckPreAllIsActive(index)||temp.bIsActive)//需要的比有的大，则不能强化
			{
				bCanStrengthen=false;
				break;
			}
		}
		if(bCanStrengthen)
		{
			//这里处理强化逻辑，注意不要错
			if(index==0)
			{
				StrengthenManager->SetCellIsActiveByIndex(index,true);
				StrengthenManager->Save();
				StrengthenByName(FString("BaseAttack"),10);
				for(int i=0;i<temp.NeededItems.Num();i++)
				{
					WarehouseManager->RemoveItem(temp.NeededItems[i].ItemId,temp.NeededItems[i].CurrentOwnedCnt);
				}
				WarehouseManager->SaveData();
				UpdatePadInfo();
				SaveToSlot();
				return true;
			}
			if(index==1)
			{
				StrengthenManager->SetCellIsActiveByIndex(index,true);
				StrengthenManager->Save();
				StrengthenByName(FString("MaxHealth"),100);
				for(int i=0;i<temp.NeededItems.Num();i++)
				{
					WarehouseManager->RemoveItem(temp.NeededItems[i].ItemId,temp.NeededItems[i].CurrentOwnedCnt);
				}
				WarehouseManager->SaveData();
				UpdatePadInfo();
				SaveToSlot();
				return true;
			}
			if(index==2)
			{
				StrengthenManager->SetCellIsActiveByIndex(index,true);
				StrengthenManager->Save();
				StrengthenByName(FString("BaseResistance"),10);
				for(int i=0;i<temp.NeededItems.Num();i++)
				{
					WarehouseManager->RemoveItem(temp.NeededItems[i].ItemId,temp.NeededItems[i].CurrentOwnedCnt);
				}
				WarehouseManager->SaveData();
				UpdatePadInfo();
				SaveToSlot();
				return true;
			}
			return false;
		}
	return false;
}



