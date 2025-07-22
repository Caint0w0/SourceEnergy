// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGAS/AS/MyEnemyAttributeSet.h"

void UMyEnemyAttributeSet::LogMes()
{
	UE_LOG(LogTemp,Warning,TEXT("UMyEnemyAttributeSet-->LogMes-->Start"));
	UE_LOG(LogTemp,Warning,TEXT("BaseAttack->CurrentValue==%f"),BaseAttack.GetCurrentValue());
	UE_LOG(LogTemp,Warning,TEXT("BaseAttack->BaseValue==%f"),BaseAttack.GetBaseValue());
	UE_LOG(LogTemp,Warning,TEXT("MaxHealth->CurrentValue==%f"),MaxHealth.GetCurrentValue());
	UE_LOG(LogTemp,Warning,TEXT("MaxHealth->BaseValue==%f"),MaxHealth.GetBaseValue());
	UE_LOG(LogTemp,Warning,TEXT("CurrentHealth->CurrentValue==%f"),CurrentHealth.GetCurrentValue());
	UE_LOG(LogTemp,Warning,TEXT("CurrentHealth->BaseValue==%f"),CurrentHealth.GetBaseValue());
	UE_LOG(LogTemp,Warning,TEXT("UMyEnemyAttributeSet-->LogMes-->End"));
}
