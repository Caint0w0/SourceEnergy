// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnemyBase.h"
#include "GameFramework/Character.h"
#include "Items/WareHouseManager.h"
#include "MyEnemy.generated.h"

struct FMyItemInfo;
struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyHealthChangeEvent, float, NewHealth);
UCLASS()
class ARPG_CPLUS_API AMyEnemy : public AMyEnemyBase{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEnemy();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Items")
	TArray<FMyItemInfo> RewardItems;
	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnEnemyHealthChangeEvent HealthChangeEvent;
	
	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
	
	void InitAbilityActorInfo();
	UFUNCTION(BlueprintImplementableEvent)
	void AfterInitAbility();
	UFUNCTION(BlueprintImplementableEvent)
	void OnApplyAttack(AActor* Player);
	UFUNCTION(BlueprintCallable)
	float CalFinalDamageValue(float AttackMulti,float Resistance);
	UFUNCTION(BlueprintCallable)
	float CalFinalStaggerValue(float StaggerMulti,float Resistance);
	UFUNCTION(BlueprintCallable)
	void Test();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
