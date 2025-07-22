// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_SpawnAttackDetect.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_CPLUS_API UANS_SpawnAttackDetect : public UAnimNotifyState
{
	GENERATED_BODY()
	public:
        // 设置要生成的 Actor 类（可以在编辑器中设置）
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
        TSubclassOf<AActor> ActorToSpawn;
    
        // 设置生成 Actor 的位置（相对角色）
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
        FTransform SpawnTransform;
	
        UFUNCTION(BlueprintCallable)
		void SpawnAttackArea();
	
        // 存储生成的 Actor
        AActor* SpawnedActor;
};
