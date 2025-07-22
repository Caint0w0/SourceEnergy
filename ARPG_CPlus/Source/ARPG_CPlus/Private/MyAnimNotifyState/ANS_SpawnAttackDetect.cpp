// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState/ANS_SpawnAttackDetect.h"

void UANS_SpawnAttackDetect::SpawnAttackArea()
{
    if (!ActorToSpawn) return;
    // 在指定位置和旋转生成 Actor
    UWorld* World = GetWorld();
    if (World)
    {
        SpawnedActor = World->SpawnActor<AActor>(ActorToSpawn, SpawnTransform);
    }
}
