// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerAttributeSet.h"

#include "Items/WarehouseManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerData.h"
UMyPlayerAttributeSet::UMyPlayerAttributeSet()
{
	// 从槽位加载游戏
	bool bIsSaveGameExist=UGameplayStatics::DoesSaveGameExist(FString("PlayerAttributes"), 0);
	
	if(bIsSaveGameExist)
	{
		UMyPlayerData*  LoadedPlayerData= Cast<UMyPlayerData>(UGameplayStatics::LoadGameFromSlot(FString("PlayerAttributes"), 0));
		InitPlayerAttributeSet(LoadedPlayerData->GetSavedAttributes());
		//UE_LOG(LogTemp,Warning,TEXT("LoadPlayerAttributes"));
		//UE_LOG(LogTemp,Warning,TEXT("CurrentHealth==%f"),LoadedPlayerData->GetSavedAttributes().CurrentHealth);
	}
	else
	{
		UMyPlayerData*  LoadedPlayerData=NewObject<UMyPlayerData>();
		//构造新的
		FSavedAttributes ASToSave=FSavedAttributes(100,
			100,
			100,
			100,
			10,
			10,
			10,
			0.5,
			0.5,
			1.1,
			1.2,
			1.3,
			1.4,
			3.2,
			1.4,
			2.0,
			6.0,
			3.0);
		//用这个新的FSavedAttributes初始化AS
		InitPlayerAttributeSet(ASToSave);
		//保存到槽位里
		LoadedPlayerData->SetSavedAttributes(ASToSave);
		//UE_LOG(LogTemp,Warning,TEXT("On Construct New AttributeSet"));
		//UE_LOG(LogTemp,Warning,TEXT("CurrentHealth==%f"),ASToSave.CurrentHealth);
		
		UGameplayStatics::SaveGameToSlot(LoadedPlayerData,FString("PlayerAttributes"),0);
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("DataTable'/Game/Data/DataTable/AttributeModItemsData.AttributeModItemsData'"));
	if (DataTableAsset.Succeeded())
	{
		BuffItemsDataTable = DataTableAsset.Object;
		//UE_LOG(LogTemp,Warning,TEXT("Item DataTable Load Success"));
		//ModAttribute(TArray<int> {100});
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("MyPlayerAttributeSet-->OnConstruct"));
}
void UMyPlayerAttributeSet::InitPlayerAttributeSet(FSavedAttributes savedAttribute)
{
	MaxHealth.SetBaseValue(savedAttribute.MaxHealth);
	CurrentHealth.SetBaseValue(MaxHealth.GetBaseValue());
	MaxStamina.SetBaseValue(savedAttribute.MaxStamina);
	CurrentStamina.SetBaseValue(MaxStamina.GetBaseValue());
	BaseAttack.SetBaseValue(savedAttribute.BaseAttack);
	BaseStagger.SetBaseValue(savedAttribute.BaseStagger);
	BaseResistance.SetBaseValue(savedAttribute.BaseResistance);
	CRT.SetBaseValue(savedAttribute.CRT);
	CriticalDamage.SetBaseValue(savedAttribute.CriticalDamage);
	NA_1_Multi.SetBaseValue(savedAttribute.NA_1_Multi);
	NA_2_Multi.SetBaseValue(savedAttribute.NA_2_Multi);
	NA_3_Multi.SetBaseValue(savedAttribute.NA_3_Multi);
	NA_4_Multi.SetBaseValue(savedAttribute.NA_4_Multi);
	NA_5_Multi.SetBaseValue(savedAttribute.NA_5_Multi);
	SpecialSkill_1_Multi.SetBaseValue(savedAttribute.SpecialSkill_1_Multi);
	SpecialSkill_2_Multi.SetBaseValue(savedAttribute.SpecialSkill_2_Multi);
	PowerSkillSumMulti.SetBaseValue(savedAttribute.PowerSkillSumMulti);
	DodgeAttackSumMulti.SetBaseValue(savedAttribute.DodgeAttackSumMulti);
	
	MaxHealth.SetCurrentValue(savedAttribute.MaxHealth);
	CurrentHealth.SetCurrentValue(MaxHealth.GetBaseValue());
	MaxStamina.SetCurrentValue(savedAttribute.MaxStamina);
	CurrentStamina.SetCurrentValue(MaxStamina.GetBaseValue());
	BaseAttack.SetCurrentValue(savedAttribute.BaseAttack);
	BaseStagger.SetCurrentValue(savedAttribute.BaseStagger);
	BaseResistance.SetCurrentValue(savedAttribute.BaseResistance);
	CRT.SetCurrentValue(savedAttribute.CRT);
	CriticalDamage.SetCurrentValue(savedAttribute.CriticalDamage);
	NA_1_Multi.SetCurrentValue(savedAttribute.NA_1_Multi);
	NA_2_Multi.SetCurrentValue(savedAttribute.NA_2_Multi);
	NA_3_Multi.SetCurrentValue(savedAttribute.NA_3_Multi);
	NA_4_Multi.SetCurrentValue(savedAttribute.NA_4_Multi);
	NA_5_Multi.SetCurrentValue(savedAttribute.NA_5_Multi);
	SpecialSkill_1_Multi.SetCurrentValue(savedAttribute.SpecialSkill_1_Multi);
	SpecialSkill_2_Multi.SetCurrentValue(savedAttribute.SpecialSkill_2_Multi);
	PowerSkillSumMulti.SetCurrentValue(savedAttribute.PowerSkillSumMulti);
	DodgeAttackSumMulti.SetCurrentValue(savedAttribute.DodgeAttackSumMulti);
}
FSavedAttributes UMyPlayerAttributeSet::ASToFSavedAttribute()
{
	FSavedAttributes temp;
	temp.MaxHealth=MaxHealth.GetBaseValue();
	temp.CurrentHealth=CurrentHealth.GetBaseValue();
	temp.MaxStamina=MaxStamina.GetBaseValue();
	temp.CurrentStamina=CurrentStamina.GetBaseValue();
	temp.BaseAttack=BaseAttack.GetBaseValue();
	temp.BaseStagger=BaseStagger.GetBaseValue();
	temp.BaseResistance=BaseResistance.GetBaseValue();
	temp.CRT=CRT.GetBaseValue();
	temp.CriticalDamage=CriticalDamage.GetBaseValue();
	temp.NA_1_Multi=NA_1_Multi.GetBaseValue();
	temp.NA_2_Multi=NA_2_Multi.GetBaseValue();
	temp.NA_3_Multi=NA_3_Multi.GetBaseValue();
	temp.NA_4_Multi=NA_4_Multi.GetBaseValue();
	temp.NA_5_Multi=NA_5_Multi.GetBaseValue();
	temp.SpecialSkill_1_Multi=SpecialSkill_1_Multi.GetBaseValue();
	temp.SpecialSkill_2_Multi=SpecialSkill_2_Multi.GetBaseValue();
	temp.PowerSkillSumMulti=PowerSkillSumMulti.GetBaseValue();
	temp.DodgeAttackSumMulti=DodgeAttackSumMulti.GetBaseValue();
	return temp;
}

void UMyPlayerAttributeSet::ModAttribute(TArray<int> ItemsId)
{
	UMyPlayerData*  LoadedPlayerData= Cast<UMyPlayerData>(UGameplayStatics::LoadGameFromSlot(FString("PlayerAttributes"), 0));
	InitPlayerAttributeSet(LoadedPlayerData->GetSavedAttributes());
	//LogBaseValueMes();
	TArray<FAttributeModifier> Sum{};//不受bIsPercent限制
	for(int i:ItemsId)
	{
		CalModMagnitude(i,Sum);
	}
	//UE_LOG(LogTemp,Warning,TEXT("Sum[0]-->ModName=%s PercentValue=%f AddedValue=%f"),*Sum[0].AttributeName,Sum[0].PercentValue,Sum[0].AddedValue);
	for(FAttributeModifier Modifier:Sum)
	{
		//UE_LOG(LogTemp,Warning,TEXT("Sum-->ModName=%s PercentValue=%f AddedValue=%f"),*Modifier.AttributeName,Modifier.PercentValue,Modifier.AddedValue);
		ApplyModifier(Modifier);
	}
	//LogBaseValueMes();
}

void UMyPlayerAttributeSet::CalModMagnitude(int ItemId,TArray<FAttributeModifier>& Modifiers)
{
	if(!BuffItemsDataTable)return;
	// 获取DataTable的所有行
	TArray<FName> RowNames= BuffItemsDataTable->GetRowNames();

	// 遍历找到ItemId对应的装备
	for (const auto& RowName : RowNames)
	{
		FAttrModItemData* RowData = BuffItemsDataTable->FindRow<FAttrModItemData>(RowName,FString(""),true);

		if (RowData->ItemId == ItemId)
		{
			for(FAttributeModifier ModifierToCal:RowData->AttributeMods)//遍历ItemId对应的装备的所有增强属性
			{
				//对于每一个要增强的属性
				bool bIsFind{false};//先记录最终修改器里有没有这个属性
				for(FAttributeModifier& Modifier:Modifiers)
				{
					if(Modifier.AttributeName.Equals(ModifierToCal.AttributeName))//找到了对应的属性
					{
						bIsFind=true;//标记为找到了
						if(ModifierToCal.bIsPercent)//根据是否百分比增幅累加对应值
						{
							Modifier.PercentValue+=ModifierToCal.PercentValue;
							//UE_LOG(LogTemp,Warning,TEXT("Percent==%f"),Modifier.PercentValue);
						}
						else
						{
							Modifier.AddedValue+=ModifierToCal.AddedValue;
						}
						//UE_LOG(LogTemp,Warning,TEXT("ModName=%s PercentValue=%f AddedValue=%f"),*Modifier.AttributeName,Modifier.PercentValue,Modifier.AddedValue);
						break;
					}
				}
				if(!bIsFind)
				{
					//要保证没用到的值为0
					Modifiers.Add(ModifierToCal);
				}
				//UE_LOG(LogTemp,Warning,TEXT("ModToCal-->ModName=%s PercentValue=%f AddedValue=%f"),*ModifierToCal.AttributeName,ModifierToCal.PercentValue,ModifierToCal.AddedValue);
				//UE_LOG(LogTemp,Warning,TEXT("OnEveryModAttribute"));
			}


			//TODO:赋予能力
			
		}
	}
}

void UMyPlayerAttributeSet::ApplyModifier(FAttributeModifier& Modifier)
{
	if(Modifier.AttributeName.Equals(FString("MaxHealth")))
	{
		FinalModAttribute(Modifier,MaxHealth);return;
	}
	if(Modifier.AttributeName.Equals(FString("MaxStamina")))
	{
		FinalModAttribute(Modifier,MaxStamina);return;
	}
	if(Modifier.AttributeName.Equals(FString("BaseAttack")))
	{
		FinalModAttribute(Modifier,BaseAttack);return;
	}
	if(Modifier.AttributeName.Equals(FString("BaseStagger")))
	{
		FinalModAttribute(Modifier,BaseStagger);return;
	}
	if(Modifier.AttributeName.Equals(FString("BaseResistance")))
	{
		FinalModAttribute(Modifier,BaseResistance);return;
	}
	if(Modifier.AttributeName.Equals(FString("CRT")))
	{
		FinalModAttribute(Modifier,CRT);return;
	}
	if(Modifier.AttributeName.Equals(FString("CriticalDamage")))
	{
		FinalModAttribute(Modifier,CriticalDamage);return;
	}
	UE_LOG(LogTemp,Warning,TEXT("ApplyModifier-->Attribute is mistake"));
}

void UMyPlayerAttributeSet::FinalModAttribute(const FAttributeModifier& Modifier,FGameplayAttributeData& Attribute)
{
	//UE_LOG(LogTemp,Warning,TEXT("FinalModAttribute-->ModName=%s PercentValue=%f AddedValue=%f"),*Modifier.AttributeName,Modifier.PercentValue,Modifier.AddedValue);
	Attribute.SetBaseValue((Attribute.GetBaseValue()+Modifier.AddedValue)*(1+Modifier.PercentValue));
	Attribute.SetCurrentValue(Attribute.GetBaseValue());
}

void UMyPlayerAttributeSet::LogBaseValueMes()const 
{
	UE_LOG(LogTemp,Warning,TEXT("UMyPlayerAttributeSet::LogBaseValueMes-->Start"));
	UE_LOG(LogTemp,Warning,TEXT("MaxHealth==%f"),MaxHealth.GetBaseValue());
	UE_LOG(LogTemp,Warning,TEXT("MaxStamina==%f"),MaxStamina.GetBaseValue());
	UE_LOG(LogTemp,Warning,TEXT("BaseAttack==%f"),BaseAttack.GetBaseValue());
	UE_LOG(LogTemp,Warning,TEXT("BaseStagger==%f"),BaseStagger.GetBaseValue());
	UE_LOG(LogTemp,Warning,TEXT("BaseResistance==%f"),BaseResistance.GetBaseValue());
	UE_LOG(LogTemp,Warning,TEXT("CRT==%f"),CRT.GetBaseValue());
	UE_LOG(LogTemp,Warning,TEXT("CriticalDamage==%f"),CriticalDamage.GetBaseValue());
	UE_LOG(LogTemp,Warning,TEXT("UMyPlayerAttributeSet::LogBaseValueMes-->End"));
}
