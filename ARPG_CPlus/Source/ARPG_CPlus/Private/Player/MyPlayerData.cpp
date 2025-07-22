// Fill out your copyright notice in the Description page of Project Settings.
#include "Player/MyPlayerData.h"

#include "Player/MyPlayerAttributeSet.h"

UMyPlayerData::UMyPlayerData()
{
	slotName="1";	
	/*savedAttributes.MaxHealth=100;
	savedAttributes.CurrentHealth=100;
	savedAttributes.MaxStamina=100;
	savedAttributes.CurrentStamina=100;
	savedAttributes.BaseAttack=10;
	savedAttributes.BaseStagger=10;
	savedAttributes.BaseResistance=5;
	savedAttributes.CRT=0.2;
	savedAttributes.CriticalDamage=0.5;
	savedAttributes.NA_1_Multi=1.1;
	savedAttributes.NA_2_Multi=1.2;
	savedAttributes.NA_3_Multi=1.3;
	savedAttributes.NA_4_Multi=1.4;
	savedAttributes.NA_5_Multi=3.2;*/
}
FSavedAttributes UMyPlayerData::GetSavedAttributes()
{
	return savedAttributes;
}
void UMyPlayerData::SetSavedAttributes(FSavedAttributes attributes)
{
	savedAttributes=attributes;
}
