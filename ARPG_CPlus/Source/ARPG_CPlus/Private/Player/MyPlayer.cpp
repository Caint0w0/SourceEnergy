// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayer.h"


#include "MaterialHLSLTree.h"
#include "AbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "DamageType/MyDamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyGAS/AS/MyEnemyAttributeSet.h"
#include "Player/MyPlayerController.h"
#include "UI/MyPlayerUI.h"
#include "Player/MyPlayerData.h"
#include "Player/MyAnimInstance.h"
#include "Player/MyPlayerAttributeSet.h"
#include "Player/MyPlayerState.h"
#include "DamageType/MyDamageType.h"
#include"Quest//QuestManagerComponent.h"
#include "Items/BagManager.h"

// Sets default values
AMyPlayer::AMyPlayer(){
	PrimaryActorTick.bCanEverTick = true;
    BagManager=CreateDefaultSubobject<UBagManager>(TEXT("BagManager"));//放前面防止AS要用到里面的东西
    QuestManagerComponent=CreateDefaultSubobject<UQuestManagerComponent>(TEXT("QuestManagerComponent"));
    
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AttributeSet = CreateDefaultSubobject<UMyPlayerAttributeSet>(TEXT("AttributeSet"));

    MyPlayerAttributeSet=Cast<UMyPlayerAttributeSet>(AttributeSet);

    
    
    MyPlayerState_SM=EMyPlayerStateSM::None;
    CanContinueNormalAttack=true;
    SpecialSkillBar_ValidLength=0.3;
    SpecialSkill_Cnt=0;
    
    UE_LOG(LogTemp, Warning, TEXT("AMyPlayer-->OnConstruct"));
}
void AMyPlayer::InitAbilityActorInfo()
{
    if (AbilitySystemComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("AMyPlayer::InitAbilityActorInfo->ASC is valid"));
        AbilitySystemComponent->InitAbilityActorInfo(this,this);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AMyPlayer::InitAbilityActorInfo->ASC is not valid"));
    }
}

void AMyPlayer::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    InitAbilityActorInfo();
    if(PlayerHUD)
    {
        PlayerHUD->AddToViewport();
        PlayerHUD->SetIsFocusable(true); // 设置为可聚焦
    }
    UE_LOG(LogTemp,Warning,TEXT("AMyPlayer::PossessedBy()"));
}

void AMyPlayer::BeginPlay()
{
    Super::BeginPlay();

    InitAbilityActorInfo();
    
    PlayerController = Cast<AMyPlayerController>(Controller);
    // 获取玩家增强输入子系统
    if (PlayerController)
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = 
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            // 启动输入映射上下文
            InputSubsystem->AddMappingContext(IM_Game, 0); // 0为优先级
        }
    }
    //赋予能力
    if(GA_Dodge)
    {
        FGameplayAbilitySpec AbilitySpec(GA_Dodge, 1, 0);
        AbilitySystemComponent->GiveAbility(AbilitySpec);
    }
    if(GA_DodgeAttack)
    {
        FGameplayAbilitySpec AbilitySpec(GA_DodgeAttack, 1, 0);
        AbilitySystemComponent->GiveAbility(AbilitySpec);
    }
    if(GA_SpecialSkillIn)
    {
        FGameplayAbilitySpec AbilitySpec(GA_SpecialSkillIn, 1, 0);
        AbilitySystemComponent->GiveAbility(AbilitySpec);
    }
    if(GA_SpecialSkillOut)
    {
        FGameplayAbilitySpec AbilitySpec(GA_SpecialSkillOut, 1, 0);
        AbilitySystemComponent->GiveAbility(AbilitySpec);
    }
    if(GA_PowerAttack)
    {
        FGameplayAbilitySpec AbilitySpec(GA_PowerAttack, 1, 0);
        AbilitySystemComponent->GiveAbility(AbilitySpec);
    }
    if(GA_NormalAttack.Num()>0)
    {
        // 遍历并添加每段普攻
        for(TSubclassOf<UGameplayAbility> GA_Temp:GA_NormalAttack )
        {
            AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(GA_Temp, 1, 0));
        }
    }
    
    //绑定属性变化的回调函数
    if(AbilitySystemComponent)
    {
        //当生命值被修改后，执行OnHealthAttributeChanged（）函数
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UMyPlayerAttributeSet, CurrentHealth)))
        .AddUObject(this, &AMyPlayer::OnHealthAttributeChanged);
    }
    AnimInstance=Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
    comboSumCnt=Combo.Num();
    comboCnt=0;

}
void AMyPlayer::UpdateModifiedPlayerAS()
{
    TArray<int> ModsId{};
    for(FMyItemInfo info:BagManager->Armor)
    {
        ModsId.Add(info.ItemId);
    }
    Cast<UMyPlayerAttributeSet>(AttributeSet)->ModAttribute(ModsId);
}


void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // 绑定移动输入
        EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyPlayer::OnMove);
        EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &AMyPlayer::OnMoveCompleted);
        EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyPlayer::OnLook);
        EnhancedInputComponent->BindAction(IA_NormalAttack, ETriggerEvent::Triggered, this, &AMyPlayer::OnCombo);
        EnhancedInputComponent->BindAction(IA_Dodge, ETriggerEvent::Triggered, this, &AMyPlayer::OnDodge);
        EnhancedInputComponent->BindAction(IA_SpecialSkill, ETriggerEvent::Triggered, this, &AMyPlayer::OnSpecialSkillIn);
        EnhancedInputComponent->BindAction(IA_SpecialSkillReleased, ETriggerEvent::Triggered, this, &AMyPlayer::OnSpecialSkillOut);
        EnhancedInputComponent->BindAction(IA_PowerAttack, ETriggerEvent::Triggered, this, &AMyPlayer::OnPowerAttack);
        EnhancedInputComponent->BindAction(IA_InterAct, ETriggerEvent::Triggered, this, &AMyPlayer::OnInterAct);
        EnhancedInputComponent->BindAction(IA_Bag, ETriggerEvent::Triggered, this, &AMyPlayer::OnIA_Bag);
        EnhancedInputComponent->BindAction(IA_QuestPad, ETriggerEvent::Triggered, this, &AMyPlayer::OnIA_QuestPad);
        EnhancedInputComponent->BindAction(IA_Esc, ETriggerEvent::Triggered, this, &AMyPlayer::OnIA_Esc);
        EnhancedInputComponent->BindAction(IA_AltIn, ETriggerEvent::Triggered, this, &AMyPlayer::OnIA_AltIn);
        EnhancedInputComponent->BindAction(IA_AltOut, ETriggerEvent::Triggered, this, &AMyPlayer::OnIA_AltOut);
    }
}
void AMyPlayer::OnSpecialSkillIn(const FInputActionValue& Value)
{
    if(GA_SpecialSkillIn)
    {
        AbilitySystemComponent->TryActivateAbilityByClass(GA_SpecialSkillIn);
        UE_LOG(LogTemp,Warning,TEXT("AbilitySystemComponent->TryActivateAbilityByClass(GA_SpecialSkillIn)"));
    }
}
void AMyPlayer::OnSpecialSkillOut(const FInputActionValue& Value)
{
    //AbilitySystemComponent->TryActivateAbilityByClass(GA_SpecialSkillIn);
    UE_LOG(LogTemp,Warning,TEXT("AbilitySystemComponent->TryActivateAbilityByClass(GA_SpecialSkillOut)"));
    if(SpecialSkillBar_Percent>=0.4&&SpecialSkillBar_Percent<=(0.4+SpecialSkillBar_ValidLength))
    {
        SpecialSkill_isStrengthen=true;
    }
    else
    {
        SpecialSkill_isStrengthen=false;
    }
    if(GA_SpecialSkillOut)
    {
        AbilitySystemComponent->TryActivateAbilityByClass(GA_SpecialSkillOut);
    }
}
void AMyPlayer::UpdateSpecialSkillBar(float DeltaTime)
{
    if(SpecialSkillBar_isUpdate==false)return;
    if(SpecialSkillBar_isIncreasing)
    {
        SpecialSkillBar_Percent += DeltaTime * SpecialSkillBar_Speed;
        if (SpecialSkillBar_Percent >= 1.0f)
        {
            SpecialSkillBar_Percent = 1.0f;
            SpecialSkillBar_isIncreasing = false;
        }
    }
    else
    {
        SpecialSkillBar_Percent -= DeltaTime * SpecialSkillBar_Speed;
        if (SpecialSkillBar_Percent <= 0.0f)
        {
            SpecialSkillBar_Percent = 0.0f;
            SpecialSkillBar_isIncreasing = true;
        }
    }
    //UE_LOG(LogTemp,Warning,TEXT("SpecialBarPercent==%f"),SpecialSkillBar_Percent);
}

void AMyPlayer::OnPowerAttack(const FInputActionValue& Value)
{
    if(GA_PowerAttack)
    {
        AbilitySystemComponent->TryActivateAbilityByClass(GA_PowerAttack);
        UE_LOG(LogTemp,Warning,TEXT("AbilitySystemComponent->TryActivateAbilityByClass(GA_PowerAttack)"));
    }
}
void AMyPlayer::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
    HealthChangeEvent.Broadcast(Data.NewValue);
}


//添加移动输入
void AMyPlayer::OnMove(const FInputActionValue& Value) {

    if(canStopMontage)
    {
        AnimInstance->Montage_Stop(0.2f);
        canStopMontage=false;
    }
    FVector2D MovementVector = Value.Get<FVector2D>();
    //UE_LOG(LogTemp, Warning, TEXT("x==%lf y==%lf"),MovementVector.X, MovementVector.Y);

    MoveX=MovementVector.X;
    MoveY=MovementVector.Y;

    const FRotator ControlRotation = Controller->GetControlRotation();
    const FRotator YawRotation = FRotator(0.0f, ControlRotation.Yaw, 0.0f);

    const FVector ForawrdDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(ForawrdDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);
}

void AMyPlayer::OnMoveCompleted(const FInputActionValue& Value)
{
    MoveX=0.0f;
    MoveY=0.0f;
}


void AMyPlayer::OnLook(const FInputActionValue& Value) {

    FVector2D LookVector = Value.Get<FVector2D>();
    if (Controller)
    {
        AddControllerYawInput(LookVector.X);
        AddControllerPitchInput(LookVector.Y);
    }
}

void AMyPlayer::OnCombo(const FInputActionValue& Value)
{
    UE_LOG(LogTemp,Warning,TEXT("OnCombo"));
    if (AbilitySystemComponent&&GA_NormalAttack.Num()>0)
    {
        FGameplayTag MyTag = FGameplayTag::RequestGameplayTag(FName("Ability.Dodge.Active"));
        //UE_LOG(LogTemp,Warning,TEXT("AbilitySystemComponent->HasMatchingGameplayTag(Ability.Dodge.Active)==%d"),AbilitySystemComponent->HasMatchingGameplayTag(MyTag));
        //UE_LOG(LogTemp,Warning,TEXT("isSuccessfullyDodged==%d"),isSuccessfullyDodged);
        //UE_LOG(LogTemp,Warning,TEXT("CanContinueNormalAttack==%d"),CanContinueNormalAttack);
        if (AbilitySystemComponent->HasMatchingGameplayTag(MyTag)&&isSuccessfullyDodged==true)
        {
            if(GA_DodgeAttack)
            {
                AbilitySystemComponent->TryActivateAbilityByClass(GA_DodgeAttack);
                UE_LOG(LogTemp,Warning,TEXT("AbilitySystemComponent->TryActivateAbilityByClass(GA_DodgeAttack)"));
            }
        }
        else if(CanContinueNormalAttack)
        {
            if(comboCnt>=0&&comboCnt<GA_NormalAttack.Num())//防止数组越界
            {
                AbilitySystemComponent->TryActivateAbilityByClass(GA_NormalAttack[comboCnt]);
                //注意添加新的行为时根据需要修改能否继续连招
                UE_LOG(LogTemp,Warning,TEXT("AbilitySystemComponent->TryActivateAbilityByClass(GA_NormalAttack%d)"),comboCnt);
            }
        }
        else
        {
            UE_LOG(LogTemp,Warning,TEXT("OnCombo-->Else"));
        }
    }
    else
    {
        
    }
}
void AMyPlayer::OnComboCallBack(EMyAttackType attacktype)
{
    if(attacktype==EMyAttackType::NormalAttack)
    {
        OnCombo(FInputActionValue());
    }
}



// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(isInterpRotateValid)
    {
        InterpRotateTimer+=DeltaTime;
        if(InterpRotateTimer>=0.2f)
        {
            isInterpRotateValid=false;

            InterpRotateTimer=0.0f;
        }
    }
    UpdateInputDirection();
    UpdateInterpPlayerRotation(DeltaTime);
    UpdateSpecialSkillBar(DeltaTime);
    //UE_LOG(LogTemp,Warning,TEXT("ComboCnt==%d"),comboCnt);
}


void AMyPlayer::SetActorYawToControlYaw()
{
    SetActorRotation(FRotator(GetActorRotation().Pitch, GetControlRotation().Yaw, GetActorRotation().Roll));
}

void AMyPlayer::UpdateInputDirection()
{
    if(MoveX==0&&MoveY>0)
    {
        InputDirection=EMoveInputDirection::F;
        targetInterpRotation=FRotator(GetActorRotation().Pitch,(int)(GetControlRotation().Yaw)%360,GetActorRotation().Roll);
    }
    else if(MoveX==0&&MoveY<0)
    {
        InputDirection=EMoveInputDirection::B;
        targetInterpRotation=FRotator(GetActorRotation().Pitch,(int)(GetControlRotation().Yaw-180)%360,GetActorRotation().Roll);
    }
    else if(MoveX>0&&MoveY==0)
    {
        InputDirection=EMoveInputDirection::R;
        targetInterpRotation=FRotator(GetActorRotation().Pitch,(int)(GetControlRotation().Yaw+90)%360,GetActorRotation().Roll);
    }
    else if(MoveX<0&&MoveY==0)
    {
        InputDirection=EMoveInputDirection::L;
        targetInterpRotation=FRotator(GetActorRotation().Pitch,(int)(GetControlRotation().Yaw-90)%360,GetActorRotation().Roll);
    }
    else if(MoveX<0&&MoveY>0)
    {
        InputDirection=EMoveInputDirection::LF;
        targetInterpRotation=FRotator(GetActorRotation().Pitch,(int)(GetControlRotation().Yaw-45)%360,GetActorRotation().Roll);
    }
    else if(MoveX<0&&MoveY<0)
    {
        InputDirection=EMoveInputDirection::LB;
        targetInterpRotation=FRotator(GetActorRotation().Pitch,(int)(GetControlRotation().Yaw-135)%360,GetActorRotation().Roll);
    }
    else if(MoveX>0&&MoveY>0)
    {
        InputDirection=EMoveInputDirection::RF;
        targetInterpRotation=FRotator(GetActorRotation().Pitch,(int)(GetControlRotation().Yaw+45)%360,GetActorRotation().Roll);
    }
    else if(MoveX>0&&MoveY<0)
    {
        InputDirection=EMoveInputDirection::RB;
        targetInterpRotation=FRotator(GetActorRotation().Pitch,(int)(GetControlRotation().Yaw+135)%360,GetActorRotation().Roll);
    }
    else
    {
        InputDirection=EMoveInputDirection::None;
        targetInterpRotation=GetActorRotation();
    }
}
void AMyPlayer::UpdateInterpPlayerRotation(float DeltaTime)
{
    FRotator currentRotation=GetActorRotation();
    if(isInterpRotateValid)
    {
        currentRotation=FMath::RInterpTo(currentRotation,targetInterpRotation,DeltaTime,15.0f);
        SetActorRotation(currentRotation);
    }
}
void AMyPlayer::OnDodge(const FInputActionValue& Value)
{
    if (AbilitySystemComponent&&GA_Dodge)
    {
        // 激活GAList[0](GA_Dodge)
        AbilitySystemComponent->TryActivateAbilityByClass(GA_Dodge);
        UE_LOG(LogTemp,Warning,TEXT("OnDodge"));
    }
}

float AMyPlayer::CalFinalDamageValue(float AttackMulti, float Resistance)
{
    UMyPlayerAttributeSet* AS=Cast<UMyPlayerAttributeSet>(AttributeSet);
    bool isCritical=false;
    if(AS->GetCRT()>0)
    {
        float temp=FMath::FRandRange(0.0, 1.0);
        isCritical=temp<AS->GetCRT();
    }
    if(isCritical)
    {
        UE_LOG(LogTemp,Warning,TEXT("isCritical:%f"),-1*(AS->GetBaseAttack()*AttackMulti*(1+AS->GetCriticalDamage())-Resistance));
        float DamageWithoutResistance=AS->GetBaseAttack()*AttackMulti*(1.0+AS->GetCriticalDamage());
        if(DamageWithoutResistance<Resistance)
        {
            return -1.0;
        }
        return -1.0*(DamageWithoutResistance-Resistance);
    }
    float DamageWithoutResistance=AS->GetBaseAttack()*AttackMulti;
    if(DamageWithoutResistance<Resistance)
    {
        return -1.0;
    }
    UE_LOG(LogTemp,Warning,TEXT("isNotCritical:%f"),-1.0*((AS->GetBaseAttack()*AttackMulti)-Resistance));
    return -1.0*(DamageWithoutResistance-Resistance);
}

float AMyPlayer::CalFinalStaggerValue(float StaggerMulti, float Resistance)
{
    UMyPlayerAttributeSet* AS=Cast<UMyPlayerAttributeSet>(AttributeSet);
    return AS->GetBaseStagger()*StaggerMulti-Resistance;
}
FVector AMyPlayer::CalculateLerpLocation(float SumTime,float CurrentTime,float DividingLine1,float DividingLine2,FVector StartLocation,FVector TargetLocation)
{
    if(DividingLine1<0||DividingLine1>1||DividingLine2<0||DividingLine2>1||DividingLine1>DividingLine2)
    {
        UE_LOG(LogTemp,Warning,TEXT("AMyPlayer::CalculateLerpLocation-->使用不符合要求"));
        return FVector::ZeroVector;
    }
    float CurrentTimePer=CurrentTime/SumTime;
    if(CurrentTimePer<=DividingLine1)
    {
        return FMath::Lerp(StartLocation,TargetLocation,CurrentTimePer/DividingLine1);
    }
    else if(CurrentTimePer<=DividingLine2&&CurrentTimePer>DividingLine1)
    {
        return TargetLocation;
    }
    else
    {
        return FMath::Lerp(TargetLocation,StartLocation,(CurrentTimePer-DividingLine2)/(1.0-DividingLine2));
    }
}

float AMyPlayer::GetCurrentAttackMulti()
{
    MyPlayerAttributeSet=Cast<UMyPlayerAttributeSet>(AttributeSet);
    if(myAttackType==EMyAttackType::NormalAttack)
    {
        if(comboCnt==1)
        {
            return Cast<UMyPlayerAttributeSet>(AttributeSet)->NA_1_Multi.GetCurrentValue();
        }
        if(comboCnt==2)
        {
            return Cast<UMyPlayerAttributeSet>(AttributeSet)->NA_2_Multi.GetCurrentValue();
        }
        if(comboCnt==3)
        {
            return Cast<UMyPlayerAttributeSet>(AttributeSet)->NA_3_Multi.GetCurrentValue();
        }
        if(comboCnt==4)
        {
            return Cast<UMyPlayerAttributeSet>(AttributeSet)->NA_4_Multi.GetCurrentValue();
        }
        if(comboCnt==0)
        {
            return Cast<UMyPlayerAttributeSet>(AttributeSet)->NA_5_Multi.GetCurrentValue()/4.0;
        }
    }
    if(myAttackType==EMyAttackType::DodgeAttack)
    {
        UE_LOG(LogTemp,Warning,TEXT("GetCurrentAttackMulti-->DodgeAttack"));
        return Cast<UMyPlayerAttributeSet>(AttributeSet)->DodgeAttackSumMulti.GetCurrentValue()/5.0;
    }
    if(myAttackType==EMyAttackType::SpecialSkill)
    {
        UE_LOG(LogTemp,Warning,TEXT("GetCurrentAttackMulti-->SpecialSkill"));
        if(SpecialSkill_Cnt==0)
        {
            return Cast<UMyPlayerAttributeSet>(AttributeSet)->SpecialSkill_1_Multi.GetCurrentValue();
        }
        if(SpecialSkill_Cnt==1)
        {
            return Cast<UMyPlayerAttributeSet>(AttributeSet)->SpecialSkill_2_Multi.GetCurrentValue();
        }
    }
    if(myAttackType==EMyAttackType::PowerAttack)
    {
        //return Cast<UMyPlayerAttributeSet>(AttributeSet)->PowerSkillSumMulti.GetCurrentValue()/8.0;
        return 0.1f;
    }
    UE_LOG(LogTemp,Warning,TEXT("GetCurrentAttackMulti-->Para is not right"));
    return 1.0f;
}
