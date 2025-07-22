// Fill out your copyright notice in the Description page of Project Settings.




#include "CameraSystem/MyPlayerCameraManager.h"
#include "CoreMinimal.h" 
#include "Player/MyPlayerController.h"
#include "Player/MyPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetSystemLibrary.h>



AMyPlayerCameraManager::AMyPlayerCameraManager() {
    //构造函数初始化数值
    CustomFOV = 90.f;
    //骨骼网格体
    CameraSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("CameraMesh");
    CameraSkeletalMesh->SetupAttachment(GetRootComponent());
}



void AMyPlayerCameraManager::OnPossess(APawn* NewPawn) {
    ControllerPawn = NewPawn;
    if(NewPawn)
    {
        //UE_LOG(LogTemp, Warning, TEXT("AMyPlayerCameraManager::OnPossess,NewPawn is Valid"));
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("AMyPlayerCameraManager::OnPossess,NewPawn is not Valid"));
    }
    if(ControllerPawn)
    {
        Player=Cast<AMyPlayer>(NewPawn);
       // UE_LOG(LogTemp, Warning, TEXT("AMyPlayerCameraManager::OnPossess,ControllerPawn is Valid"));
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("AMyPlayerCameraManager::OnPossess,ControllerPawn is not Valid"));
    }
    bIsInitialized=true;
    //UE_LOG(LogTemp, Warning, TEXT("AMyPlayerCameraManager::OnPossess,bIsInitialized==%d"),bIsInitialized);
}

void AMyPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
    Super::UpdateViewTarget(OutVT, DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("AMyPlayerCameraManager::UpdateViewTarget,bIsInitialized==%d"),bIsInitialized);
    if(!bIsInitialized)return;
    if(ControllerPawn)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Pawn is Valid"));
    }
    
    OutVT.POV.FOV = CustomFOV;    //设置自定义的视野范围(FOV)

    TargetCameraRotation = CalculateTargetRotation();
    TargetCameraLocation = CalculateTargetLocation();
    
    bool trace=false;
    FHitResult HitResult;
    TArray<AActor*> IgnoreActors;
    
    TEnumAsByte<EDrawDebugTrace::Type>a;
    FVector TraceStart=FVector(0.0f,0.0f,0.0f);
    if(Player)
    {
        a=Player->DebugType;
        TraceStart=Player->GetMesh()->GetSocketLocation("Camera");
    }
    else
    {
        a=EDrawDebugTrace::None;
    }
    //TraceTypeQuery2:Camera
    UKismetSystemLibrary::SphereTraceSingle(GetWorld(),
        TraceStart,
        TargetCameraLocation,
        10.0f,
        TraceTypeQuery1,
        trace,
        IgnoreActors,
        a,
        HitResult,
        false,
        FLinearColor::Red,
        FLinearColor::Green,
        10.0f);

    if(HitResult.IsValidBlockingHit())
    {
        TargetCameraLocation=HitResult.Location;
        //UE_LOG(LogTemp,Warning,TEXT("Collided"));
    }

    

    OutVT.POV.Location = TargetCameraLocation; 
    OutVT.POV.Rotation= TargetCameraRotation;

    //UE_LOG(LogTemp, Warning, TEXT("a"));
}

FRotator  AMyPlayerCameraManager::CalculateTargetRotation() {
   if(!ControllerPawn)return GetCameraRotation();
    //UE_LOG(LogTemp, Warning, TEXT("Rotation Updating"));
   return FMath::RInterpTo(GetCameraRotation(), ControllerPawn->GetControlRotation(), UGameplayStatics::GetWorldDeltaSeconds(ControllerPawn),RotationInterpSpeed);
   //当前CameraRotation插值到ControlRotation
}

FVector AMyPlayerCameraManager::CalculateAxisIndependentLag(FVector CurrentLocation, FVector TargetLocation, FRotator CameraRotation, FVector LagSpeed,const float DeltaTime) {

    FRotator RotationYaw = FRotator(0.0f, 0.0f, CameraRotation.Yaw);
    const auto RelativeCurrentLocation{ RotationYaw.UnrotateVector(CurrentLocation) };
    const auto RelativeTargetLocation{ RotationYaw.UnrotateVector(TargetLocation) };

    //Todo：用动画状态机更新LagSpeed

    return RotationYaw.RotateVector({
        FMath::FInterpTo(RelativeCurrentLocation.X, RelativeTargetLocation.X, DeltaTime, LagSpeed.X),
        FMath::FInterpTo(RelativeCurrentLocation.Y, RelativeTargetLocation.Y, DeltaTime, LagSpeed.Y),
        FMath::FInterpTo(RelativeCurrentLocation.Z, RelativeTargetLocation.Z, DeltaTime, LagSpeed.Z)
        });
}

FVector AMyPlayerCameraManager::CalculateTargetLocation() {
    if(!ControllerPawn)return GetCameraLocation();
    FTransform PivotTarget = ControllerPawn->GetActorTransform();
    //锚点为actor中心
    //未来可更换为插槽位置
    //Todo:PivotLagSpeed
    SmoothedPivotTarget.SetLocation(CalculateAxisIndependentLag(SmoothedPivotTarget.GetLocation(), PivotTarget.GetLocation(),TargetCameraRotation , PivotLagSpeed ,UGameplayStatics::GetWorldDeltaSeconds(ControllerPawn)));

    return SmoothedPivotTarget.GetLocation() + UKismetMathLibrary::GetForwardVector(TargetCameraRotation) * OffsetX +
    UKismetMathLibrary::GetRightVector(TargetCameraRotation)*OffsetY+
    UKismetMathLibrary::GetUpVector(TargetCameraRotation)*OffsetZ;
}


