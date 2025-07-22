// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MyWeaponCollisionComponent.h"

#include "DamageType/MyDamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyWeapon.h"
#include "Player/MyPlayerData.h"

// Sets default values for this component's properties
UMyWeaponCollisionComponent::UMyWeaponCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UMyWeaponCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
	Weapon=Cast<AMyWeapon>(GetOwner());
	
	//传进来Player
	if(!Player)
	{
		UE_LOG(LogTemp,Warning,TEXT("MyWeaponCollisionComponent's Player is NULL"));
	}
	// ...
}


// Called every frame
void UMyWeaponCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DamageTrace();
	// ...
}

void UMyWeaponCollisionComponent::DamageTrace()
{
	if(Player)
	{
		if (Player->isAttacking)
		{
			TArray<FHitResult> HitResults;
			TArray<AActor*> IgnoreActors;
			TEnumAsByte<EDrawDebugTrace::Type> a=Player->DebugType;
			bool isHit=UKismetSystemLibrary::SphereTraceMulti(GetWorld(),
			Weapon->SM_WeaponComponent->GetSocketLocation("A"),
			Weapon->SM_WeaponComponent->GetSocketLocation("B"),
			5.0f,
			TraceTypeQuery3,
			false,
			IgnoreActors,
			a,
			HitResults,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			10.0f);

			if(isHit)
			{
				for(int i=0;i<HitResults.Num();i++)
				{
					HitActor=HitResults[i].GetActor();
					if(!HitedActors.Contains(HitActor))
					{
						HitedActors.Add(HitActor);
						Player->OnApplyAttack(HitActor);
					}
				}
			}
		}
		else
		{
			HitedActors.Empty();
		}
	}
}


