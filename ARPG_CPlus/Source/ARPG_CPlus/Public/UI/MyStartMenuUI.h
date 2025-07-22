// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidgetBase.h"
#include "MyStartMenuUI.generated.h"

UCLASS()
class ARPG_CPLUS_API UMyStartMenuUI : public UMyUserWidgetBase
{
	GENERATED_BODY()
public:
	
	UMyStartMenuUI();

protected:
	virtual void NativeConstruct() override;
};
