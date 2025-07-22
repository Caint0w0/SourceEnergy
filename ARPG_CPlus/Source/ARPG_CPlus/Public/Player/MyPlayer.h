#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyPlayerBase.h"
#include "Character/MyCharacterBase.h"
#include "Enemy/MyEnemy.h"
#include "Enum/My_Enum.h"
#include "GameFramework/Character.h"
#include "Items/WarehouseManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyPlayer.generated.h"


class UQuestManagerComponent;
class UBagManager;
struct FMyDamageInfo;
class UMyDamageType;
class AMyEnemy;
struct FOnAttributeChangeData;
class UMyPlayerUI;
class UMyPlayerAttributeSet;
class UGameplayAbility;
class AMyWeapon;
class UMyPlayerData;
class UMyAnimInstance;
class AMyPlayerController;

USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FMyDamageInfo
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Stagger;
	
	FMyDamageInfo()
	{
		Damage=0;
		Stagger=0;
	}
	FMyDamageInfo(float Damage, float Stagger)
	{
		this->Damage=Damage;
		this->Stagger=Stagger;
	}
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeEvent, float, NewHealth);

UCLASS() 

class ARPG_CPLUS_API AMyPlayer : public AMyCharacterBase
{

	GENERATED_BODY() 

public:
	UFUNCTION()
	void InitAbilityActorInfo();
protected:
	virtual void PossessedBy(AController* NewController) override;
public: 
	// Sets default values for this character's properties 
	AMyPlayer();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyPlayerAttributeSet* MyPlayerAttributeSet;
	UFUNCTION(BlueprintCallable)
	void UpdateModifiedPlayerAS();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBagManager* BagManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UQuestManagerComponent* QuestManagerComponent;
	
	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnHealthChangeEvent HealthChangeEvent;
	
	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|PlayerController")
	TObjectPtr<AMyPlayerController> PlayerController;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|PlayerHUD")
	TObjectPtr<UMyPlayerUI> PlayerHUD;
	
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "MyPlayer|GAS");
	TSubclassOf<UGameplayAbility> GA_Dodge;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "MyPlayer|GAS");
	TSubclassOf<UGameplayAbility> GA_DodgeAttack;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "MyPlayer|GAS");
	TSubclassOf<UGameplayAbility> GA_SpecialSkillIn;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "MyPlayer|GAS");
	TSubclassOf<UGameplayAbility> GA_SpecialSkillOut;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "MyPlayer|GAS");
    TArray<TSubclassOf<UGameplayAbility>> GA_NormalAttack;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "MyPlayer|GAS");
	TSubclassOf<UGameplayAbility> GA_PowerAttack;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	UInputMappingContext* IM_Game;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	UInputAction* IA_Look;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	UInputAction* IA_Dodge;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	UInputAction* IA_NormalAttack;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	UInputAction* IA_SpecialSkill;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	UInputAction* IA_SpecialSkillReleased;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	UInputAction* IA_PowerAttack;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	UInputAction* IA_InterAct;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	TObjectPtr<UInputAction> IA_Bag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	TObjectPtr<UInputAction> IA_QuestPad;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	TObjectPtr<UInputAction> IA_Esc;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	TObjectPtr<UInputAction> IA_AltIn;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyPlayer|Input")
	TObjectPtr<UInputAction> IA_AltOut;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnInterAct();

	UFUNCTION(BlueprintImplementableEvent)
	void OnIA_Bag();

	UFUNCTION(BlueprintImplementableEvent)
	void OnIA_Esc();

	UFUNCTION(BlueprintImplementableEvent)
	void OnIA_AltIn();

	UFUNCTION(BlueprintImplementableEvent)
	void OnIA_AltOut();

	UFUNCTION(BlueprintImplementableEvent)
	void OnIA_QuestPad();

	//GameFlowControl
	UFUNCTION(BlueprintImplementableEvent)
	void OnFirstInGame();
	//
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "MyPlayer|Input")
	EMoveInputDirection InputDirection=EMoveInputDirection::None;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|DebugType")
	TEnumAsByte<EDrawDebugTrace::Type> DebugType=EDrawDebugTrace::None;
	

	void OnMove(const FInputActionValue& Value);
	void OnMoveCompleted(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);
	void OnDodge(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void OnCombo(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void OnSpecialSkillIn(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void OnSpecialSkillOut(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void OnPowerAttack(const FInputActionValue& Value);
	
	void SetActorYawToControlYaw();
	void UpdateInputDirection();
	void UpdateInterpPlayerRotation(float DeltaTime);
//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Interp")
	bool isInterpRotateValid=false;
	float InterpRotateTimer=0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Interp")
	FRotator targetInterpRotation=FRotator::ZeroRotator;

	//SpecialSkill相关的变量
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|SpecialSkill")
	float SpecialSkillBar_Percent=0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|SpecialSkill")
	float SpecialSkillBar_Speed=1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|SpecialSkill")
	float SpecialSkillBar_ValidLength=0.3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|SpecialSkill")
	bool SpecialSkillBar_isIncreasing=true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|SpecialSkill")
	bool SpecialSkillBar_isUpdate=false;
	void UpdateSpecialSkillBar(float DeltaTime);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|SpecialSkill")
	bool SpecialSkill_isStrengthen=false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|SpecialSkill")
	int SpecialSkill_Cnt=0;

	//DodgeAttack相关的变量
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MyPlayer|DodgeAttack")
	float DodgeAttack_SumTime=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MyPlayer|DodgeAttack")
	float DodgeAttack_CurrentTime=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MyPlayer|DodgeAttack")
	FVector DodgeAttack_TargetLocation;
	UFUNCTION(BlueprintCallable)
	FVector CalculateLerpLocation(float SumTime,float CurrentTime,float DividingLine1,float DividingLine2,FVector StartLocation,FVector TargetLocation);
	//PowerAttack 相关
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MyPlayer|PowerAttack")
	TArray<AActor*> Targets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MyPlayer|PowerAttack")
	float PowerAttack_SumTime;

	
	UFUNCTION(BlueprintCallable)
	void OnComboCallBack(EMyAttackType attacktype);

	
	//用一个GE代表一次攻击的所有信息，倍率在GE中设置:传入的基础攻击*伤害倍率、传入的基础失衡值*GE中设置的倍率、要上的标签
	//标签单纯是标签或者触发别的GA，GA来应用新的GE上buff
	//
	//
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "MyPlayer|Attack")
	EMyAttackType myAttackType=EMyAttackType::None;
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void OnApplyAttack(AActor* Enemy);
	UFUNCTION(BlueprintCallable)
	float CalFinalDamageValue(float AttackMulti,float Resistance);
	UFUNCTION(BlueprintCallable)
	float CalFinalStaggerValue(float StaggerMulti,float Resistance);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|InputBoolValues")
	bool canStopMontage=false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MyPlayer|InputValues")
	float MoveX=0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MyPlayer|InputValues")
	float MoveY=0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "MyPlayer|Movement")
	EGait gait;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Attack")
	bool isAttacking=false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Attack")
	int comboSumCnt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Attack")
	bool CanAttack=true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Attack")
	bool isLocking=false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Attack")
	bool CanContinueNormalAttack=true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Attack")
	int comboCnt=0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Attack")
	UMyAnimInstance* AnimInstance;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Attack")
	TArray<UAnimMontage*> Combo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Dodge")
	TArray<UAnimMontage*> Dodge;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Dodge")
	bool isSuccessfullyDodged=false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MyPlayer|Dodge")
	int inAttackAreaCnt=0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|EnemyValues")
	FVector TargetEnemyLocation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Weapon")
	AMyWeapon* Weapon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|State")
	EMyPlayerStateSM MyPlayerState_SM=EMyPlayerStateSM::None;

	UFUNCTION(BlueprintCallable)
	float GetCurrentAttackMulti();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|Quest")
	TArray<FMyItemInfo> QuestRewards{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|InterAct")
	TArray<FMyItemInfo> PickUpItems;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "MyPlayer|InterAct")
	TObjectPtr<AActor> TriggerActorRef;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnGetRewardsItems();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
