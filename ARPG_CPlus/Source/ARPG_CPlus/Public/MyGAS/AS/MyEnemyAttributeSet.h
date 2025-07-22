// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyEnemyAttributeSet.generated.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UMyEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void LogMes();
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_AS")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyEnemyAttributeSet, MaxHealth);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_AS")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UMyEnemyAttributeSet, CurrentHealth);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_AS")
	FGameplayAttributeData BaseAttack;
	ATTRIBUTE_ACCESSORS(UMyEnemyAttributeSet, BaseAttack);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_AS")
	FGameplayAttributeData BaseStagger;
	ATTRIBUTE_ACCESSORS(UMyEnemyAttributeSet, BaseStagger);
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_AS")
	FGameplayAttributeData PhysicResistance;
	ATTRIBUTE_ACCESSORS(UMyEnemyAttributeSet, PhysicResistance);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_AS")
	FGameplayAttributeData IceResistance;
	ATTRIBUTE_ACCESSORS(UMyEnemyAttributeSet, IceResistance);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_AS")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UMyEnemyAttributeSet, FireResistance);
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_AS")
	FGameplayAttributeData BeStaggerMultiplier;
	ATTRIBUTE_ACCESSORS(UMyEnemyAttributeSet, BeStaggerMultiplier);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_AS")
	FGameplayAttributeData CurrentStaggerValue;
	ATTRIBUTE_ACCESSORS(UMyEnemyAttributeSet, CurrentStaggerValue);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy_AS")
	FGameplayAttributeData MaxStaggerValue;
	ATTRIBUTE_ACCESSORS(UMyEnemyAttributeSet, MaxStaggerValue);
	//
	
};
