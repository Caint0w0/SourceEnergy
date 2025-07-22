// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"

UCLASS()
class ARPG_CPLUS_API AMyWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyWeapon();
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category="root" )
	USceneComponent* root;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category="SM" )
	UStaticMeshComponent* SM_WeaponComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
