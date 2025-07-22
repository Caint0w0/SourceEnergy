// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/MyPlayer.h"
#include "MyWeaponCollisionComponent.generated.h"


class AMyWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_CPLUS_API UMyWeaponCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyWeaponCollisionComponent();

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Reference")
	AMyPlayer* Player;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Values")
	TArray<AActor*> HitedActors;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Values")
	AActor* HitActor;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Values")
	AMyWeapon* Weapon;

	void DamageTrace();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
