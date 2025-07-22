// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/My_Enum.h"
#include "GameFramework/Actor.h"
#include "Interface/MyInterActInterface.h"
#include "Items/WareHouseManager.h"
#include "InterActTrigger.generated.h"

class UWidgetComponent;
class UBoxComponent;

UCLASS()
class ARPG_CPLUS_API AInterActTrigger : public AActor,public IMyInterActInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterActTrigger();

	virtual void OnInterAct_Implementation(APawn* InstigatorPawn)override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "InterActTrigger")
	TObjectPtr<UBoxComponent> BoxCollision;
	// 开始重叠事件
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 结束重叠事件
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
