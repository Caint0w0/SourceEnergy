#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerData.h"
#include "MyPlayerController.generated.h"


UCLASS()
class ARPG_CPLUS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	
	AMyPlayerController();
	
	//Called when a controller possesses a Pawn
	virtual void OnPossess(APawn* InPawn)override;
	
	UFUNCTION(BlueprintCallable)
	void OnLevelLoaded(FString& CurrentLevelName);
	
};