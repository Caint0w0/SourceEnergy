// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacterBase.h"
#include "MyEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API AMyEnemyBase : public AMyCharacterBase
{
	GENERATED_BODY()
public:
	AMyEnemyBase();
protected:
	virtual void BeginPlay() override;
};
