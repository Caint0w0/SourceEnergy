#include "Player/MyPlayerController.h"
#include "CameraSystem/MyPlayerCameraManager.h"
#include "GameInstance/MyGameInstance.h"

AMyPlayerController::AMyPlayerController() {
	UE_LOG(LogTemp,Warning,TEXT("AMyPlayerController-->OnConstruct"));
}
void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();
}
void AMyPlayerController::OnLevelLoaded(FString& CurrentLevelName)
{
	UE_LOG(LogTemp,Warning,TEXT("AMyPlayerController-->OnLevelLoaded"));
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	
	if(CurrentLevelName.Equals(MyGameInstance->StartMenuString))
	{
		bShowMouseCursor=true;
		const FInputModeUIOnly Input{FInputModeUIOnly()};
		SetInputMode(Input);
	}
	else if(CurrentLevelName.Equals(MyGameInstance->MyMainString))
	{
		if(MyGameInstance->bIsFirstInGameInGameInstance)
		{
			UE_LOG(LogTemp,Warning,TEXT("MyGameInstance->bIsFirstInGameInGameInstance is true"));
			MyGameInstance->bIsFirstInGameInGameInstance=false;
			if(MyGameInstance->GameFlowKeyPointsInGameInstance.Num()==0)
			{
				MyGameInstance->GameFlowKeyPointsInGameInstance.Add(false);
				MyGameInstance->SaveGameFlow();
			}
			MyGameInstance->GameFlowKeyPointsInGameInstance[0]=false;//保证第一次进入时都是false
			AMyPlayer* MyPlayerRef=Cast<AMyPlayer>(GetPawn());
			if(MyPlayerRef)
			{
				MyPlayerRef->OnFirstInGame();
			}
			bShowMouseCursor=false;
			const FInputModeUIOnly Input{FInputModeUIOnly()};
			SetInputMode(Input);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("MyGameInstance->bIsFirstInGameInGameInstance is false"));
		
			bShowMouseCursor=false;
			const FInputModeGameOnly Input{FInputModeGameOnly()};
			SetInputMode(Input);
		}
		
	}
}

void AMyPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp,Warning,TEXT("AMyPlayerController::OnPossess"));
	if(InPawn)
	{
		if (AMyPlayerCameraManager* CameraManager = Cast<AMyPlayerCameraManager>(PlayerCameraManager)) {
			UE_LOG(LogTemp,Warning,TEXT("AMyPlayerController-->CameraManager-->OnPossess"));
			CameraManager->OnPossess(InPawn);
		}
	}
}
	
