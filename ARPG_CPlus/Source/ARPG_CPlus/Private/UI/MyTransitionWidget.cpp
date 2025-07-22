// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyTransitionWidget.h"

#include "Animation/WidgetAnimation.h"

void UMyTransitionWidget::PlayTransitionIn()
{
	if(TransitionIn)
	{
		PlayMyAnimation(TransitionIn);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("UMyTransitionWidget::PlayTransitionIn()-->TransitionIn is not Valid"));
	}
}
void UMyTransitionWidget::PlayTransitionOut()
{
	if(TransitionOut)PlayMyAnimation(TransitionOut);
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("UMyTransitionWidget::PlayTransitionOut()-->TransitionOut is not Valid"));
	}
}
void UMyTransitionWidget::NativeConstruct(){
	Super::NativeConstruct();

	// 确保动画播放完成时触发事件
	if (TransitionIn)
	{
		// 注册动画完成事件
		OnFTransitionInFinished.BindDynamic(this,&UMyTransitionWidget::OnTransitionInFinished);
		BindToAnimationFinished(TransitionIn, OnFTransitionInFinished);
		
		OnFTransitionOutFinished.BindDynamic(this,&UMyTransitionWidget::OnTransitionOutFinished);
		BindToAnimationFinished(TransitionOut, OnFTransitionOutFinished);
	}
}
void UMyTransitionWidget::OnTransitionInFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("Transition In Finished"));
	// 通知GameInstance过渡动画已经完成
	if (OnFTransitionInFinishedDelegate.IsBound())
	{
		OnFTransitionInFinishedDelegate.Broadcast();
	}
}
void UMyTransitionWidget::OnTransitionOutFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("Transition Out Finished"));
	// 通知GameInstance过渡动画已经完成
	if (OnFTransitionOutFinishedDelegate.IsBound())
	{
		OnFTransitionOutFinishedDelegate.Broadcast();
	}
}