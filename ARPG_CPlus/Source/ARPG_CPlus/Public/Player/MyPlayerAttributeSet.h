// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGAS/MyAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyPlayerAttributeSet.generated.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
struct FAttributeModifier;
struct FSavedAttributes;
/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UMyPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UMyPlayerAttributeSet();
	//读取装备属性相关
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player_AS")
	UDataTable* BuffItemsDataTable;
	
	UFUNCTION(BlueprintCallable, Category = "Player_AS")
	void ModAttribute(TArray<int> ItemsId);

	UFUNCTION(BlueprintCallable, Category = "Player_AS")
	void CalModMagnitude(int ItemId,TArray<FAttributeModifier>& Modifiers);
	
	UFUNCTION(BlueprintCallable, Category = "Player_AS")
	void ApplyModifier(FAttributeModifier& Modifier);

	UFUNCTION(BlueprintCallable, Category = "Player_AS")
	void FinalModAttribute(const FAttributeModifier& Modifier,FGameplayAttributeData& Attribute);

	UFUNCTION(BlueprintCallable, Category = "Player_AS")
	void LogBaseValueMes()const;

	//---------------------------------
	
	UFUNCTION()
	void InitPlayerAttributeSet(FSavedAttributes savedAttribute);
	UFUNCTION()
	FSavedAttributes ASToFSavedAttribute();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData MaxHealth;//
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, MaxHealth);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, CurrentHealth);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData MaxStamina;//
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, MaxStamina);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, CurrentStamina);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData BaseAttack;//
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, BaseAttack);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData BaseStagger;//
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, BaseStagger);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData BaseResistance;//
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, BaseResistance);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData CRT;//
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, CRT);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData CriticalDamage;//
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, CriticalDamage);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData NA_1_Multi;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, NA_1_Multi);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData NA_2_Multi;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, NA_2_Multi);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData NA_3_Multi;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, NA_3_Multi);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData NA_4_Multi;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, NA_4_Multi);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData NA_5_Multi;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, NA_5_Multi);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData SpecialSkill_1_Multi;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, SpecialSkill_1_Multi);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData SpecialSkill_2_Multi;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, SpecialSkill_2_Multi);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData PowerSkillSumMulti;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, PowerSkillSumMulti);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player_AS")
	FGameplayAttributeData DodgeAttackSumMulti;
	ATTRIBUTE_ACCESSORS(UMyPlayerAttributeSet, DodgeAttackSumMulti);
};
