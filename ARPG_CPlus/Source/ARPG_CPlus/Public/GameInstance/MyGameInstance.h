#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"


class UMyPlayerData;
class UMyStartMenuUI;
class ULevelStreamingDynamic;
class UMediaTexture;
class UMediaPlayer;
class UMyTransitionWidget;

UCLASS()
class ARPG_CPLUS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	//Some const Variable To Manage Levels
	const FString ManagerString{FString("Manager")};
	const FString MyMainString{FString("MyMain")};
	const FString StartMenuString{FString("StartMenu")};
	const FString Level1String{FString("Level1")};
	//
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="GameInstance|Values")
	FVector StartMenuLocation{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="GameInstance|TSoftObjectPtr<UWorld>")
	TSoftObjectPtr<UWorld> MyMainLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="GameInstance|TSoftObjectPtr<UWorld>")
	TSoftObjectPtr<UWorld> StartLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="GameInstance|TSoftObjectPtr<UWorld>")
	TSoftObjectPtr<UWorld> Level1;
	//
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="GameInstance|Widget")
	TSubclassOf<UUserWidget> TransitionWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="GameInstance|Widget")
	TSubclassOf<UUserWidget> StartMenuWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="GameInstance|Widget")
	TObjectPtr<UMyTransitionWidget> TransitionWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="GameInstance|Widget")
	TObjectPtr<UMyStartMenuUI> StartMenuWidget;
	
	UFUNCTION(BlueprintCallable,Category="GameInstance|Widget")
	void ShowTransitionWidget();
	
	UFUNCTION(BlueprintCallable,Category="GameInstance|Widget")
	void HideTransitionWidget();
	
	UFUNCTION(BlueprintCallable,Category="GameInstance|Widget")
	void OnTransitionInFinished();
	
	UFUNCTION(BlueprintCallable,Category="GameInstance|Widget")
	void OnTransitionOutFinished();
	
	UFUNCTION(BlueprintCallable,Category="GameInstance|Widget")
	void ShowStartMenu();
	
	UFUNCTION(BlueprintCallable,Category="GameInstance|Widget")
	void ClearAllWidgets(UWorld* World);
	//-----------------------------------------------------------------------------

	//LevelLoaded CallBack
	UFUNCTION(BlueprintCallable)
	void OnLevelLoaded();
	UFUNCTION(BlueprintCallable)
	void OnLevelUnLoaded()const;
	
	UFUNCTION(BlueprintCallable)
	void SwitchLevelWithTransition(const FString& LevelName);

	UFUNCTION(BlueprintCallable)
	void LoadMapByMyOwnName(FString& MapName)const;
	UFUNCTION(BlueprintCallable)
	void UnLoadMapByMyOwnName(FString& MapName)const;

	//Manage GameFlow
	UFUNCTION(BlueprintCallable,Category="GameInstance|GameFlowControl")
	bool SaveGameFlow()const;
	UFUNCTION(BlueprintCallable,Category="GameInstance|GameFlowControl")
	bool LoadGameFlow();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameInstance|GameFlowControl")
	bool bIsFirstInGameInGameInstance{true};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameInstance|GameFlowControl")
	TArray<bool> GameFlowKeyPointsInGameInstance;
	
	//
	
public:
    // 设置总音量
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetMasterVolume(float Volume);
    
    // 获取总音量
    UFUNCTION(BlueprintCallable, Category = "Audio")
    float GetMasterVolume() const;
    
    float MasterVolume = 1.0f;
private:
	UPROPERTY()
	FString CurrentLevelName;
	UPROPERTY()
	FString LastLevelName;
protected:
	virtual void Init() override;
	virtual void OnStart() override;
};
