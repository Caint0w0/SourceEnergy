#include "GameInstance/MyGameInstance.h"
#include "GameFramework/GameUserSettings.h"
#include "MediaSource.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "NavigationSystem.h"
#include "NavigationSystemTypes.h"

#include "Blueprint/UserWidget.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MyStartMenuUI.h"
#include "Engine/LevelStreamingDynamic.h"
#include "GameFlowControl/GameFlowControlSaveData.h"
#include "GameFramework/GameModeBase.h"
#include "Player/MyPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "Manager/MySaveManager.h"
#include "Player/MyPlayerData.h"
#include "UI/MyTransitionWidget.h"

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp,Warning,TEXT("GameInstance-->OnInit"))

	/*GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(1600, 900));
	GEngine->GetGameUserSettings()->ApplySettings(true);*/
	
	CurrentLevelName=FString("Manager");
	LastLevelName=FString("Manager");

	LoadGameFlow();
	
}

void UMyGameInstance::ShowStartMenu()
{
	UE_LOG(LogTemp,Warning,TEXT("OnShowMainMenuPersistent--Start"));
	if (!StartMenuWidget)
	{
		StartMenuWidget = CreateWidget<UMyStartMenuUI>(UGameplayStatics::GetPlayerController(GetWorld(),0), StartMenuWidgetClass);
		if(StartMenuWidget&& !StartMenuWidget->IsInViewport())
		{
			StartMenuWidget->AddToViewport();
			UE_LOG(LogTemp,Warning,TEXT("Create a new StartMenuWidget,and Added To Viewport"));
		}
		if(StartMenuWidget)
		{
			UE_LOG(LogTemp,Warning,TEXT("OnShowMainMenuPersistent,StartMenuWidget->IsInViewport()==%d"),StartMenuWidget->IsInViewport());
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("OnShowMainMenuPersistent,StartMenuWidget->Is not valid"));
		}
	}
	else
	{
		StartMenuWidget->AddToViewport();
		UE_LOG(LogTemp,Warning,TEXT("StartMenuWidget is Valid,Added To Viewport"));
	}
	UE_LOG(LogTemp,Warning,TEXT("OnShowMainMenuPersistent-->End"));
}


void UMyGameInstance::LoadMapByMyOwnName(FString& MapName)const
{
	UE_LOG(LogTemp,Warning,TEXT("UMyGameInstance::LoadMapByMyOwnName"));
	
	FLatentActionInfo LatentInfo;
	LatentInfo.UUID = FMath::Rand(); // 随机生成一个唯一的ID
	LatentInfo.Linkage = 0; // 通常设置为0

	LatentInfo.CallbackTarget=const_cast<UMyGameInstance*>(this);
	LatentInfo.ExecutionFunction = TEXT("OnLevelLoaded");
	
	if(MapName.Equals(MyMainString))
	{
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(),MyMainLevel , true, false, LatentInfo);
	}
	else if(MapName.Equals(StartMenuString))
	{
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(),StartLevel , true, true, LatentInfo);
	}
	else if(MapName.Equals(Level1String))
	{
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(),Level1 , true, false, LatentInfo);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("UMyGameInstance::LoadMapByMyOwnName-->Error!"));
	}
}
void UMyGameInstance::UnLoadMapByMyOwnName(FString& MapName)const
{
	FLatentActionInfo LatentInfo;
	LatentInfo.UUID = FMath::Rand(); // 随机生成一个唯一的ID
	LatentInfo.Linkage = 0; // 通常设置为0

	LatentInfo.CallbackTarget=const_cast<UMyGameInstance*>(this);
	LatentInfo.ExecutionFunction = TEXT("OnLevelUnLoaded");
	
	if(MapName.Equals(MyMainString))
	{
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(),MyMainLevel , LatentInfo,false);
	}
	else if(MapName.Equals(StartMenuString))
	{
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(),StartLevel , LatentInfo,false);
	}
	else if(MapName.Equals(Level1String))
	{
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(),Level1 , LatentInfo,false);
	}
	else if(MapName.Equals(FString("Manager")))
	{
		UE_LOG(LogTemp,Warning,TEXT("UMyGameInstance::UnLoadMapByMyOwnName-->Manager!"));
		OnLevelUnLoaded();
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("UMyGameInstance::UnLoadMapByMyOwnName-->Error!"));
		OnLevelUnLoaded();
	}
}
void UMyGameInstance::OnLevelLoaded()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance->OnLevelLoaded"));
	
	UWorld* World=GetWorld();
	
	AMyPlayerController* MyPlayerController=Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(World,0));
	
	if(CurrentLevelName.Equals(StartMenuString))
	{
		ShowStartMenu();
		if(MyPlayerController)
		{
			MyPlayerController->GetPawn()->SetActorLocation(FVector(200, 200, 200));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GameInstance->OnLevelLoaded-->MyPlayerController is not Valid"));
		}
	}
	else if(CurrentLevelName.Equals(MyMainString))
	{
		if(MyPlayerController)
		{
			MyPlayerController->GetPawn()->SetActorLocation(FVector(-2305.193852,1173.874136,104.600101));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GameInstance->OnLevelLoaded-->MyPlayerController is not Valid"));
		}
		StartMenuWidget->RemoveFromParent();
	}
	else if(CurrentLevelName.Equals(Level1String))
	{
		if(MyPlayerController)
		{
			MyPlayerController->GetPawn()->SetActorLocation(FVector(-12003.502543,-7483.034395,273.466514));
		}
	}

	if(MyPlayerController)
	{
		MyPlayerController->OnLevelLoaded(CurrentLevelName);
	}
	
	UnLoadMapByMyOwnName(LastLevelName);
	

}

void UMyGameInstance::ShowTransitionWidget()
{
	TransitionWidget = CreateWidget<UMyTransitionWidget>(GetWorld(), TransitionWidgetClass);
	if (TransitionWidget)
	{
		// 注册回调，等进入动画播放完成后会广播，此处响应委托
		TransitionWidget->OnFTransitionInFinishedDelegate.AddDynamic(this, &UMyGameInstance::OnTransitionInFinished);
		TransitionWidget->OnFTransitionOutFinishedDelegate.AddDynamic(this, &UMyGameInstance::OnTransitionOutFinished);

		TransitionWidget->AddToViewport();

		TransitionWidget->PlayTransitionIn();
		//UE_LOG(LogTemp, Warning, TEXT("Show Transition Widget"));
	}
}

void UMyGameInstance::HideTransitionWidget()
{
	if (TransitionWidget)
	{
		TransitionWidget->RemoveFromParent();
		UE_LOG(LogTemp,Warning,TEXT("HideTransitionWidget"));
	}
}

void UMyGameInstance::SwitchLevelWithTransition(const FString& LevelName)
{
	LastLevelName=CurrentLevelName;
	CurrentLevelName=LevelName;
	
	bool bIsShowTransition { !(LastLevelName.Equals(ManagerString)&&CurrentLevelName.Equals(StartMenuString)) };
	UE_LOG(LogTemp,Warning,TEXT("UMyGameInstance::SwitchLevelWithTransition,CurrentLevelName==%s,bIsShowTransition==%d"),*CurrentLevelName,bIsShowTransition);
	if(bIsShowTransition){
		ShowTransitionWidget();//TransitionIn动画的结束回调会加载关卡
	}
	else
	{
		LoadMapByMyOwnName(CurrentLevelName);
	}
}

void UMyGameInstance::OnTransitionInFinished()
{
	LoadMapByMyOwnName(CurrentLevelName);
}

void UMyGameInstance::OnTransitionOutFinished()
{
	HideTransitionWidget();
}

void UMyGameInstance::OnStart()
{
	Super::OnStart();
	UE_LOG(LogTemp,Warning,TEXT("GameInstance-->OnStart"));
	//SwitchLevelWithTransition(FString("StartMenu"));
	//ShowStartMenu();
	
}

void UMyGameInstance::ClearAllWidgets(UWorld* World)
{
	if (!World) return;
	TArray<UUserWidget*> AllWidgets;
	// 获取当前世界中的所有 UUserWidget
	for (TObjectIterator<UUserWidget> It; It; ++It)
	{
		UUserWidget* Widget = *It;
		if (Widget && Widget->GetWorld() == World)
		{
			AllWidgets.Add(Widget);
		}
	}
	// 从视口中移除所有 Widget
	for (const auto Widget : AllWidgets)
	{
		if (Widget)
		{
			Widget->RemoveFromParent(); // 移除视口中的 Widget
		}
	}
}

//Manage GameFlow
bool UMyGameInstance::SaveGameFlow()const
{
	UGameFlowControlSaveData* Save= Cast<UGameFlowControlSaveData>(UGameplayStatics::CreateSaveGameObject(UGameFlowControlSaveData::StaticClass()));
	if (Save)
	{
		Save->SetGameFlowKeyPoints(GameFlowKeyPointsInGameInstance);
		Save->SetIsFirstInGame(bIsFirstInGameInGameInstance);
		if (UGameplayStatics::SaveGameToSlot(Save, FString("GameFlowControlSaveData"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("UGameFlowControlSaveData::-->Save Success"));
			return true;
		}
		UE_LOG(LogTemp, Warning, TEXT("UGameFlowControlSaveData::-->Save Failed"));
	}
	return false;
}

bool UMyGameInstance::LoadGameFlow()
{
	bool bIsExistSaveData=UGameplayStatics::DoesSaveGameExist(FString("GameFlowControlSaveData"),0);
	
	if(bIsExistSaveData)
	{
		UGameFlowControlSaveData* Save=Cast<UGameFlowControlSaveData>(UGameplayStatics::LoadGameFromSlot(FString("GameFlowControlSaveData"), 0));
		GameFlowKeyPointsInGameInstance=Save->GetGameFlowKeyPoints();
		bIsFirstInGameInGameInstance=Save->GetIsFirstInGame();
		UE_LOG(LogTemp,Warning,TEXT("UGameFlowControlSaveData-->Loaded Success"));
		return true;
	}
	SaveGameFlow();
	UE_LOG(LogTemp,Warning,TEXT("UGameFlowControlSaveData-->Loaded Fail"));
	return false;
}

void UMyGameInstance::OnLevelUnLoaded()const
{
	if(TransitionWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance->OnLevelLoaded-->TransitionWidget is InViewPort:%d"),TransitionWidget->IsInViewport());
		TransitionWidget->PlayTransitionOut();//数据都处理完之后播放淡出动画
	}
}

void UMyGameInstance::SetMasterVolume(float Volume)
{
	MasterVolume = FMath::Clamp(Volume, 0.0f, 1.0f); // 限制音量范围
	//UGameplayStatics::SetSoundMixClassOverride(this, nullptr, MasterVolume, 1.0f, 0.0f);
	//待实现
}

float UMyGameInstance::GetMasterVolume() const
{
	return MasterVolume;
}