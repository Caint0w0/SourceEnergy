// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_NormalAttackBase.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UGA_NormalAttackBase : public UGameplayAbility
{
	GENERATED_BODY()
public:
	FOnGameplayAbilityCancelled OnGameplayAbilityCancelled;	
};
