// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/MyPlayerData.h"
#include "MyUserWidgetBase.generated.h"
UCLASS()
class ARPG_CPLUS_API UMyUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void LoadGame(FString SlotName);
	UFUNCTION(BlueprintCallable)
	void NewGame();
	UFUNCTION(BlueprintCallable)
	void AsyncLoadLevel(const FString& LevelName);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void PlayMyAnimation(UWidgetAnimation* Anim);
};
