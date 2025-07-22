// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidgetBase.h"
#include "Blueprint/UserWidget.h"
#include "MyTransitionWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UMyTransitionWidget : public UMyUserWidgetBase
{
	GENERATED_BODY()
public:
	// 在蓝图中绑定的动画
	UPROPERTY(BlueprintReadWrite,Category = "UI")
	UWidgetAnimation* TransitionIn;
	
	UPROPERTY(BlueprintReadWrite,Category = "UI")
	UWidgetAnimation* TransitionOut;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void PlayTransitionIn();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void PlayTransitionOut();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnTransitionInFinished();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnTransitionOutFinished();
	
	// 创建一个委托来让GameInstance接收通知
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTransitionInFinishedDelegate);
	FTransitionInFinishedDelegate OnFTransitionInFinishedDelegate;
	
	//FWidgetAnimationDynamicEvent用来绑定动画结束事件
	FWidgetAnimationDynamicEvent OnFTransitionInFinished;
	
	// 创建一个委托来让GameInstance接收通知
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTransitionOutFinishedDelegate);
	FTransitionInFinishedDelegate OnFTransitionOutFinishedDelegate;
	
	//FWidgetAnimationDynamicEvent用来绑定动画结束事件
	FWidgetAnimationDynamicEvent OnFTransitionOutFinished;

protected:
	virtual void NativeConstruct() override;
	
};
