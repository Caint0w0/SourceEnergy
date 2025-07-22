// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyCharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 初始化 AbilitySystemComponent 和 AttributeSet
	
}

// Called when the game starts or when spawned
void AMyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* AMyCharacterBase::GetAbilitySystemComponent()const
{
	return AbilitySystemComponent;
}
void AMyCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

