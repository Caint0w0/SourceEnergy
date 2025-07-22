// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/MyEnemyBase.h"

#include "Components/CapsuleComponent.h"
#include "MyGAS/MyAbilitySystemComponent.h"
#include "MyGAS/MyAttributeSet.h"
AMyEnemyBase::AMyEnemyBase()
{
	
}
void AMyEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	//AbilitySystemComponent->InitAbilityActorInfo(this,this);
}

