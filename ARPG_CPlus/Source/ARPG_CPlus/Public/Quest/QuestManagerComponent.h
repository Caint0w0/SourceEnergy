// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/WarehouseManager.h"
#include "Enum/My_Enum.h"
#include "QuestManagerComponent.generated.h"


struct FMyItemInfo;

USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FQuestNode
{
	GENERATED_USTRUCT_BODY()

	// 记录前置节点ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestNode")
	TArray<int> PredecessorNodeIDs;

	// 区分检查前置条件类型（任意一个完成或全部完成）
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestNode")
	bool bRequireAllPredecessors;

	// 记录唯一后置节点ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestNode")
	int SuccessorNodeID;

	// 记录当前节点ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestNode")
	int NodeID;

	// 标记是否完成
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestNode")
	bool bIsCompleted;
};

// 任务条件检查结构
USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FQuestCondition
{
	GENERATED_USTRUCT_BODY()

	// 当前值
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentValue;

	// 需要达到的值
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NeededValue;

	// 物品ID,0表示空信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemID{0};

	// 描述文本（可以为空）
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DescriptionText;
};

USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FQuestNodeData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	// 当前节点ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestNodeData")
	int NodeID;

	// 任务提示文本
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestNodeData")
	FString QuestHintText;

	// 任务条件检查类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestNodeData")
	EQuestType QuestType{EQuestType::None};

	// 任务条件检查结构数组
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestNodeData")
	TArray<FQuestCondition> Conditions;
};

USTRUCT(BlueprintType)
struct ARPG_CPLUS_API FQuestStructure : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// 任务ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestStructure")
	int QuestID{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestStructure")
	FString QuestName{};

	// 当前正在执行的任务节点ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestStructure")
	int CurrentNodeID{};

	// 任务节点数组
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestStructure")
	TArray<FQuestNode> QuestNodes{};

	// 结尾任务节点ID数组（任意一个完成即整个任务完成）
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestStructure")
	TArray<int> EndNodeIDs{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestStructure")
	TArray<FMyItemInfo> Rewards{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="QuestStructure")
	TArray<int> NextAcceptQuestId{};
};




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_CPLUS_API UQuestManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestManagerComponent();

	UDataTable* QuestStructureDataTable;
	UDataTable* QuestNodeDataTable;
private:
	UPROPERTY()
	int CurrentFollowQuestId{0};
public:
	UFUNCTION(BlueprintCallable,Category="QuestManagerComponent")
	int GetCurrentFollowQuestId();
	UFUNCTION(BlueprintCallable,Category="QuestManagerComponent")
	FQuestStructure GetFollowQuestStructure()const;
	UFUNCTION(BlueprintCallable)
	bool OnFollow(const int QuestId);
public:
	//要存储的数据
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="QuestManagerComponent")
	TArray<FQuestStructure> CurrentQuests{};
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="QuestManagerComponent")
	TArray<FQuestNodeData> CurrentQuestNodesData{};

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="QuestManagerComponent")
	TArray<FQuestStructure> CompletedQuests{};

	UFUNCTION(BlueprintCallable)
	bool LoadData();
	UFUNCTION(BlueprintCallable)
	bool SaveData();
	//

	UFUNCTION(BlueprintCallable)
	bool AcceptQuest(int QuestId);
	UFUNCTION(BlueprintCallable)
	bool AddToCurrentQuestsWithoutRepeat(FQuestStructure StructureToAdd);
	UFUNCTION(BlueprintCallable)
	bool CheckIsExistQuestById(int QuestId)const;

	UFUNCTION(BlueprintCallable)
	FQuestStructure GetQuestStructureById(const int QuestId)const;
	
	UFUNCTION(BlueprintCallable)
	bool CheckIsExistQuestNodeDataById(int NodeId)const;
	UFUNCTION(BlueprintCallable)
	bool CheckIsExistQuestConditionByIndex(int NodeId,int index)const;
	UFUNCTION(BlueprintCallable)
	bool CheckIsCompletedQuestById(int QuestId)const;
	
	UFUNCTION(BlueprintCallable)
	bool AddToCurrentQuestNodesDataWithoutRepeat(FQuestNodeData NodeDataToAdd);
	UFUNCTION(BlueprintCallable)
	bool AddToCompletedQuestsWithoutRepeat(FQuestStructure StructureToAdd);
	UFUNCTION(BlueprintCallable)
	FQuestNodeData GetQuestNodeDataByNodeID(int NodeID);
	UFUNCTION(BlueprintCallable)
	FQuestNode GetQuestNodeByNodeID(FQuestStructure Quest,int NodeID);
	UFUNCTION(BlueprintCallable)
	int GetQuestNodeDataIndexByNodeID(int NodeID)const;

	UFUNCTION(BlueprintCallable)
	TArray<int> GetItemTypeQuestNodeInCurrentNode()const;
	UFUNCTION(BlueprintCallable)
	TArray<int> GetRelativeQuestNodeByItemId(TArray<int> ItemRelativeQuestNodes,int itemId)const;

	UFUNCTION(BlueprintCallable)
	bool TryCommitQuestCurrentNode(int QuestId);
	
	UFUNCTION(BlueprintCallable)
	bool CompleteQuest(int QuestId);
	//CallBack
	UFUNCTION(BlueprintCallable)
	void OnCompleteQuest(int index);

	//---
	UFUNCTION(BlueprintCallable)
	void LogCurrentQuestNodesData();
	UFUNCTION(BlueprintCallable)
	void LogCurrentQuests();

	UFUNCTION(BlueprintCallable)
	bool CheckQuestNodeCompleted(int QuestNodeID);
	//Interface
	UFUNCTION(BlueprintCallable)
	bool ModQuestConditionValue(int QuestNodeId,int QuestConditionIndex,int Value);

	UFUNCTION(BlueprintCallable)
	bool UpdateConditionAndTryCommit(int ItemId,int Value);
	UFUNCTION(BlueprintCallable)
	bool CommonUpdateConditionAndTryCommit(int QuestId,int ConditionIndex,int Value);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
