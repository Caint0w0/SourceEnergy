// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "My_Enum.generated.h"

UENUM(BlueprintType)
enum class EGait : uint8
{
	None=0,
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA(DisplayName = "Run"),
	Sprint UMETA(DisplayName = "Sprint")
};

UENUM(BlueprintType)
enum class EMyAttackType : uint8
{
	None=0,
	NormalAttack UMETA(DisplayName = "NormalAttack"),
	SpecialSkill UMETA(DisplayName = "SpecialSkill"),
	PowerAttack UMETA(DisplayName = "PowerAttack"),
	DodgeAttack UMETA(DisplayName = "DodgeAttack"),
};

UENUM(BlueprintType)
enum class EMoveInputDirection: uint8
{
	None=0,
	F UMETA(DisplayName = "F"),
	B UMETA(DisplayName = "B"),
	L UMETA(DisplayName = "L"),
	R UMETA(DisplayName = "R"),
	LF UMETA(DisplayName = "LF"),
	RF UMETA(DisplayName = "RF"),
	LB UMETA(DisplayName = "LB"),
	RB UMETA(DisplayName = "RB")
};


UENUM(BlueprintType)
enum class EMyPlayerStateSM : uint8
{
	None=0,
	Movement UMETA(DisplayName = "Movement"),
	Attack UMETA(DisplayName = "Attack"),
	Dodge UMETA(DisplayName = "Dodge")
};

UENUM(BlueprintType)
enum class EMyAttackAttributeType : uint8
{
	None=0,
	Physic UMETA(DisplayName = "Physic"),
	Ice UMETA(DisplayName = "Ice"),
	Fire UMETA(DisplayName = "Fire"),
};

UENUM(BlueprintType)
enum class EMyPadType : uint8
{
	None=0,
	StrengthenPad UMETA(DisplayName = "StrengthenPad"),
	BagPad UMETA(DisplayName = "BagPad"),
	WareHouseAndBagPad UMETA(DisplayName = "WareHousePad"),
	RecipePad UMETA(DisplayName = "RecipePad"),
	QuestManagerPad UMETA(DisplayName = "QuestManagerPad"),
};

UENUM(BlueprintType)
enum class EMyItemType : uint8
{
	None=0,
	Item UMETA(DisplayName = "Item"),
	Prop UMETA(DisplayName = "Prop"),
	Arm UMETA(DisplayName = "Arm"),
	Accessory UMETA(DisplayName = "Accessory"),
	Weapon UMETA(DisplayName = "Weapon"),
};

UENUM(BlueprintType)
enum class EMyItemLocation : uint8
{
	None=0,
	Bag UMETA(DisplayName = "Bag"),
	Armed UMETA(DisplayName = "Armed"),
	WareHouse UMETA(DisplayName = "WareHouse"),
};
UENUM(BlueprintType)
enum class EMyArmType : uint8
{
	None=0,
	Helmet UMETA(DisplayName = "Helmet"),
	Chestplate UMETA(DisplayName = "Chestplate"),
	Boots UMETA(DisplayName = "Boots"),
};

// 任务条件检查类型枚举
UENUM(BlueprintType)
enum class EQuestType : uint8
{
	None=0,
	Items UMETA(DisplayName = "Items"),
	Enemy UMETA(DisplayName = "Enemy"),
	// 可以根据需要扩展
};

