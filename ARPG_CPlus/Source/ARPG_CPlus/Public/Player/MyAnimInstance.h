// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"
#include "Enum/My_Enum.h"
#include "MyAnimInstance.generated.h"


class UCharacterMovementComponent;
class AMyPlayer;
class UMyPlayerData;

UCLASS()
class ARPG_CPLUS_API UMyAnimInstance : public UAnimInstance
{

	GENERATED_BODY()  
	virtual void NativeBeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "MyUpdateFunction")
	void UpdateAnimationProperties();
public:
	UPROPERTY( BlueprintReadWrite , Category = "MovementValues")
	double AccelerationXY;

	UPROPERTY( BlueprintReadWrite , Category = "MovementValues")
	bool HasAcceleration;

	UPROPERTY( BlueprintReadWrite , Category = "MovementValues")
	double SpeedXY;

	UPROPERTY( BlueprintReadWrite , Category = "MovementValues")
	bool HasVelocity;
	
	UPROPERTY( BlueprintReadWrite , Category = "MovementValues")
	EGait Animgait= EGait::Run;

	UPROPERTY( BlueprintReadWrite , Category = "MovementValues")
	FVector WorldLocation;
	UPROPERTY( BlueprintReadWrite , Category = "MovementValues")
	double DisplacementSinceLastUpdate;
	UPROPERTY( BlueprintReadWrite , Category = "MovementValues")
	double DisplacementSpeed;
	UPROPERTY( BlueprintReadWrite , Category = "MovementValues")
	bool isFirstUpdate=true;

	TObjectPtr<AMyPlayer>Player;
	TObjectPtr<UCharacterMovementComponent> CharacterMovement;
};
