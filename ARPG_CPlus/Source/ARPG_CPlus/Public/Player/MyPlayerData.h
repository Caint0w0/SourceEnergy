#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyPlayerData.Generated.h"

class UMyPlayerAttributeSet;
class UMyAnimInstance;
class AMyWeapon;

USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FSavedAttributes
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;
	UPROPERTY(EditDefaultsOnly)
	float CurrentHealth;
	UPROPERTY(EditDefaultsOnly)
	float MaxStamina;
	UPROPERTY(EditDefaultsOnly)
	float CurrentStamina;
	UPROPERTY(EditDefaultsOnly)
	float BaseAttack;
	UPROPERTY(EditDefaultsOnly)
	float BaseStagger;
	UPROPERTY(EditDefaultsOnly)
	float BaseResistance;
	UPROPERTY(EditDefaultsOnly)
	float CRT;
	UPROPERTY(EditDefaultsOnly)
	float CriticalDamage;
	UPROPERTY(EditDefaultsOnly)
	float NA_1_Multi;
	UPROPERTY(EditDefaultsOnly)
	float NA_2_Multi;
	UPROPERTY(EditDefaultsOnly)
	float NA_3_Multi;
	UPROPERTY(EditDefaultsOnly)
	float NA_4_Multi;
	UPROPERTY(EditDefaultsOnly)
	float NA_5_Multi;
	UPROPERTY(EditDefaultsOnly)
	float SpecialSkill_1_Multi;
	UPROPERTY(EditDefaultsOnly)
	float SpecialSkill_2_Multi;
	UPROPERTY(EditDefaultsOnly)
	float PowerSkillSumMulti;
	UPROPERTY(EditDefaultsOnly)
	float DodgeAttackSumMulti;
	FSavedAttributes()
	{
		MaxHealth=0;
		CurrentHealth=0;
		MaxStamina=0;
		CurrentStamina=0;
		BaseAttack=0;
		BaseStagger=0;
		BaseResistance=0;
		CRT=0;
		CriticalDamage=0;
		NA_1_Multi=0;
		NA_2_Multi=0;
		NA_3_Multi=0;
		NA_4_Multi=0;
		NA_5_Multi=0;
		SpecialSkill_1_Multi=0;
		SpecialSkill_2_Multi=0;
		PowerSkillSumMulti=0;
		DodgeAttackSumMulti=0;
	}
	FSavedAttributes(float MaxHealth, float CurrentHealth, float MaxStamina, float CurrentStamina,float BaseAttack,
		float BaseStagger,float BaseResistance,float CRT,float CriticalDamage,float NA_1_Multi,float NA_2_Multi,float NA_3_Multi,
		float NA_4_Multi,float NA_5_Multi,float SpecialSkill_1_Multi,float SpecialSkill_2_Multi,float PowerSkillSumMulti,float DodgeAttackSumMulti)
	{
		this->MaxHealth=MaxHealth;
		this->CurrentHealth=CurrentHealth;
		this->MaxStamina=MaxStamina;
		this->CurrentStamina=CurrentStamina;
		this->BaseAttack=BaseAttack;
		this->BaseStagger=BaseStagger;
		this->BaseResistance=BaseResistance;
		this->CRT=CRT;
		this->CriticalDamage=CriticalDamage;
		this->NA_1_Multi=NA_1_Multi;
		this->NA_2_Multi=NA_2_Multi;
		this->NA_3_Multi=NA_3_Multi;
		this->NA_4_Multi=NA_4_Multi;
		this->NA_5_Multi=NA_5_Multi;
		this->SpecialSkill_1_Multi=SpecialSkill_1_Multi;
		this->SpecialSkill_2_Multi=SpecialSkill_2_Multi;
		this->PowerSkillSumMulti=PowerSkillSumMulti;
		this->DodgeAttackSumMulti=DodgeAttackSumMulti;
	}
	
};

UCLASS(Blueprintable, BlueprintType) 
class ARPG_CPLUS_API UMyPlayerData : public USaveGame
{
	GENERATED_BODY()
public:
	UMyPlayerData();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString slotName;
private:
	UPROPERTY()
	FSavedAttributes savedAttributes;
public:
	UFUNCTION(BlueprintCallable)
	FSavedAttributes GetSavedAttributes();
	UFUNCTION(BlueprintCallable)
	void SetSavedAttributes(FSavedAttributes temp);
};
