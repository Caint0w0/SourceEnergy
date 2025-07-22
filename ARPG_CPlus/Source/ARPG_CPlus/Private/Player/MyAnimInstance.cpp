// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/MyPlayer.h"
#include "Player/MyPlayerData.h"
#include "UniversalObjectLocators/AnimInstanceLocatorFragment.h"

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Player = Cast<AMyPlayer>(GetOwningActor());
	CharacterMovement=Player->GetCharacterMovement();
}


void UMyAnimInstance::UpdateAnimationProperties() {
	if(IsValid(Player))
	{
		AccelerationXY=UKismetMathLibrary::VSizeXY(CharacterMovement->GetCurrentAcceleration());
		SpeedXY=UKismetMathLibrary::VSizeXY(CharacterMovement->Velocity);

		if(AccelerationXY>0){HasAcceleration=true;}else{HasAcceleration=false;}
		if(SpeedXY>0){HasVelocity=true;}else{HasVelocity=false;}
		
		Animgait=Player->gait;
	}
	//UpdateLocomotionData(UGameplayStatics::GetWorldDeltaSeconds(Player));
}




