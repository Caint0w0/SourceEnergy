// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyWeapon.h"

// Sets default values
AMyWeapon::AMyWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root=CreateDefaultSubobject<USceneComponent>("root");
	SetRootComponent(root);
	//创建骨骼网格体组件，并附加在根组件
	SM_WeaponComponent=CreateDefaultSubobject<UStaticMeshComponent>("SM_Weapon");
	SM_WeaponComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

