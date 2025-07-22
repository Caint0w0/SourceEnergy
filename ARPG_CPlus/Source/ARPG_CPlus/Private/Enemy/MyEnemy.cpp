// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/MyEnemy.h"

#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyGAS/AS/MyEnemyAttributeSet.h"
#include "Player/MyPlayer.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AttributeSet = CreateDefaultSubobject<UMyEnemyAttributeSet>(TEXT("MyEnemyAttributeSet"));
	
	if(AttributeSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyEnemy::InitAbilityActorInfo->AttributeSet is valid"));
	}
}
void AMyEnemy::InitAbilityActorInfo()
{
	if(!AttributeSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyEnemy::InitAbilityActorInfo->AttributeSet is not valid"));
		AttributeSet = NewObject<UMyEnemyAttributeSet>(this, TEXT("AttributeSet"));
		if(AttributeSet)
		{
			UE_LOG(LogTemp, Warning, TEXT("AMyEnemy::InitAbilityActorInfo->Create Success"));
			AbilitySystemComponent->AddAttributeSetSubobject(AttributeSet);
		}
		else{return;}
	}
	
	if (AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyEnemy::InitAbilityActorInfo->ASC is valid"));
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyEnemy::InitAbilityActorInfo->ASC is not valid"));
	}
	if(AbilitySystemComponent)
	{
		//当生命值被修改后，执行OnHealthAttributeChanged（）函数
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UMyEnemyAttributeSet, CurrentHealth)))
		.AddUObject(this, &AMyEnemy::OnHealthAttributeChanged);
	}
	AfterInitAbility();
}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyEnemy::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	HealthChangeEvent.Broadcast(Data.NewValue);
}

float AMyEnemy::CalFinalDamageValue(float AttackMulti, float Resistance)
{
	const UMyEnemyAttributeSet* AS=Cast<UMyEnemyAttributeSet>(AbilitySystemComponent->GetAttributeSet(UMyEnemyAttributeSet::StaticClass()));
	/*UE_LOG(LogTemp,Warning,TEXT("SumDamage==%f"),-1.0*((AS->GetBaseAttack()*AttackMulti)-Resistance));
	UE_LOG(LogTemp,Warning,TEXT("EnemyBaseAttack==%f"),(AS->BaseAttack.GetCurrentValue()));
	UE_LOG(LogTemp,Warning,TEXT("Resistance==%f"),Resistance);*/

	if(AS->GetBaseAttack()*AttackMulti>Resistance)
	{
		return -1.0*((AS->GetBaseAttack()*AttackMulti)-Resistance);
	}
	return 1.0f;
}

float AMyEnemy::CalFinalStaggerValue(float StaggerMulti, float Resistance)
{
	const UMyEnemyAttributeSet* AS=Cast<UMyEnemyAttributeSet>(AbilitySystemComponent->GetAttributeSet(UMyEnemyAttributeSet::StaticClass()));
	if(AS->GetBaseStagger()*StaggerMulti>Resistance)
	{
		return AS->GetBaseStagger()*StaggerMulti-Resistance;
	}
	
	return 0;
	
}

void AMyEnemy::Test()
{
	OnApplyAttack(UGameplayStatics::GetPlayerPawn( GetWorld(),0));
}

