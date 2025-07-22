// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyUserWidgetBase.h"

#include "GameInstance/MyGameInstance.h"
#include "Manager/MySaveManager.h"
#include "Player/MyPlayerController.h"
#include "Player/MyPlayerData.h"
void UMyUserWidgetBase::NewGame()
{
	UMyGameInstance* gameInstance=Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if(gameInstance)
	{
		//gameInstance->NewGame();
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("UMyUserWidgetBase-->NewGame-->读取失败！"));
	}
}
void UMyUserWidgetBase::SaveGame()
{
	//有点问题之后重写

}
void UMyUserWidgetBase::LoadGame(FString SlotName)
{
	//读取数据到GameInstance的CurrentPlayerData里
	UMyGameInstance* gameInstance=Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if(gameInstance)
	{
		//gameInstance->LoadGame(SlotName);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("UMyUserWidgetBase-->LoadGame-->读取失败！"));
	}
}
void UMyUserWidgetBase::AsyncLoadLevel(const FString& LevelName)
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	MyGI->SwitchLevelWithTransition(LevelName);
}
void UMyUserWidgetBase::PlayMyAnimation(UWidgetAnimation* Anim)
{
	if (Anim)  // 确保动画已经绑定
	{
		PlayAnimation(Anim);  // 播放动画
	}
}