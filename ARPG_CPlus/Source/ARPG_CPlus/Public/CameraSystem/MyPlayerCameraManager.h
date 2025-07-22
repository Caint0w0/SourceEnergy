// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "Player/MyPlayer.h"
#include "MyPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API AMyPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()


public:
	AMyPlayerCameraManager();

	UPROPERTY(BlueprintReadWrite)
	APawn* ControllerPawn;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInitialized;

	UFUNCTION(BlueprintCallable)
	void OnPossess(APawn* NewPawn);

	UFUNCTION(BlueprintCallable)
	FVector CalculateTargetLocation();

	UFUNCTION(BlueprintCallable)
	FVector CalculateAxisIndependentLag(FVector CurrentLocation, FVector TargetLocation, FRotator CameraRotation,FVector LagSpeed,const float DeltaTime);

	UFUNCTION(BlueprintCallable)
	FRotator CalculateTargetRotation();

	UPROPERTY(BlueprintReadOnly)
	FRotator TargetCameraRotation;

	UPROPERTY(BlueprintReadOnly)
	FVector TargetCameraLocation;

	UPROPERTY(BlueprintReadOnly)
	FTransform SmoothedPivotTarget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector PivotLagSpeed=FVector(10.0f,10.0f,10.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double RotationInterpSpeed =  10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double OffsetX = -100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double OffsetY = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double OffsetZ = 100.0f;

	AMyPlayer* Player;

protected:
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	// ����Ӷ�����Զ��������Ч������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CustomFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USkeletalMeshComponent> CameraSkeletalMesh;

	
};
