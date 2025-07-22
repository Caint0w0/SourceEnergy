// Fill out your copyright notice in the Description page of Project Settings.


#include "InterAct/InterActTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Player/MyPlayer.h"
// Sets default values
AInterActTrigger::AInterActTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 创建 BoxCollision 组件
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent); // 绑定到根组件
	BoxCollision->SetBoxExtent(FVector(50.f, 50.f, 50.f)); // 设置碰撞盒的大小
	BoxCollision->SetCollisionProfileName(TEXT("Trigger"));

	
	
}

// Called when the game starts or when spawned
void AInterActTrigger::BeginPlay()
{
	Super::BeginPlay();
	// 绑定重叠事件
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AInterActTrigger::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AInterActTrigger::OnEndOverlap);
	
}

// Called every frame
void AInterActTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInterActTrigger::OnInterAct_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp,Warning,TEXT("OnInterActInC++"));
}

// 开始重叠事件
void AInterActTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Begin Overlap with: %s"), *OtherActor->GetName());
	if (OtherActor && OtherActor != this)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Begin Overlap with: %s"), *OtherActor->GetName());
		if(AMyPlayer* MyPlayer=Cast<AMyPlayer>(OtherActor))
		{
			MyPlayer->TriggerActorRef=this;
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("AInterActTrigger-->MyPlayer is Not Valid"));
		}
	}
}

// 结束重叠事件
void AInterActTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		//UE_LOG(LogTemp, Warning, TEXT("End Overlap with: %s"), *OtherActor->GetName());
		if(AMyPlayer* MyPlayer=Cast<AMyPlayer>(OtherActor))
		{
			MyPlayer->TriggerActorRef=nullptr;
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("AInterActTrigger-->MyPlayer is Not Valid"));
		}
	}
}
