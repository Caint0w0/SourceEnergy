// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestManagerComponent.h"

#include "GameInstance/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Player/MyPlayer.h"
#include "Quest/QuestSaveData.h"


// Sets default values for this component's properties
UQuestManagerComponent::UQuestManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// 加载 DataTable
	static ConstructorHelpers::FObjectFinder<UDataTable> QuestStructureDataTableFinder(TEXT("/Game/Data/DataTable/QuestStructureDataTable.QuestStructureDataTable"));
	if (QuestStructureDataTableFinder.Succeeded())
	{
		QuestStructureDataTable = QuestStructureDataTableFinder.Object;
	}
	// 加载 DataTable
	static ConstructorHelpers::FObjectFinder<UDataTable> QuestNodeDataTableFinder(TEXT("/Game/Data/DataTable/QuestNodeDataTable.QuestNodeDataTable"));
	if (QuestNodeDataTableFinder.Succeeded())
	{
		QuestNodeDataTable = QuestNodeDataTableFinder.Object;
	}
	// ...
}


// Called when the game starts
void UQuestManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	if(!LoadData())
	{
		SaveData();
	}
	//LogCurrentQuests();
	//LogCurrentQuestNodesData();
	//AcceptQuest(1);
	//LogCurrentQuests();
	//LogCurrentQuestNodesData();
	//UE_LOG(LogTemp,Warning,TEXT("CheckQuestNodeCompleted(1)==%d"),CheckQuestNodeCompleted(1));
	//CompleteQuest(1);
	//LogCurrentQuests();
	//LogCurrentQuestNodesData();
	// ...
}


// Called every frame
void UQuestManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


bool UQuestManagerComponent::AcceptQuest(int QuestId)
{
	if(!QuestStructureDataTable||!QuestNodeDataTable)return false;//DataTable无效返回false
	TArray<FName> QuestStructureRowNames= QuestStructureDataTable->GetRowNames();
	
	for (const auto& RowName : QuestStructureRowNames)
	{
		FQuestStructure* RowData = QuestStructureDataTable->FindRow<FQuestStructure>(RowName,FString(""),true);
		if(RowData->QuestID==QuestId)//找到对应的任务
		{
			AddToCurrentQuestsWithoutRepeat(*RowData);//添加到现有任务数组
			if(RowData->QuestNodes.Num()>0)
			{
				TArray<FName> QuestNodeDataRowNames= QuestNodeDataTable->GetRowNames();
				for(FQuestNode QuestNode : RowData->QuestNodes)//遍历当前任务里的所有任务节点
				{
					for (const auto& QuestNodeDataRowName : QuestNodeDataRowNames)
					{
						FQuestNodeData* QuestNodeDataRowData=QuestNodeDataTable->FindRow<FQuestNodeData>(QuestNodeDataRowName,FString(""),true);
						if(QuestNodeDataRowData&&QuestNodeDataRowData->NodeID==QuestNode.NodeID)//找到任务节点数据
						{
							AddToCurrentQuestNodesDataWithoutRepeat(*QuestNodeDataRowData);//添加到任务数据数组
							break;
						}
					}
				}
			}
			return true;
		}
	}
	return false;
}

bool UQuestManagerComponent::AddToCurrentQuestsWithoutRepeat(FQuestStructure StructureToAdd)
{
	for(FQuestStructure QuestStructure:CurrentQuests)
	{
		if(QuestStructure.QuestID==StructureToAdd.QuestID)
		{
			return false;
		}
	}
	CurrentQuests.Add(StructureToAdd);
	return true;
}

bool UQuestManagerComponent::AddToCurrentQuestNodesDataWithoutRepeat(FQuestNodeData NodeDataToAdd)
{
	for(FQuestNodeData QuestNodeData : CurrentQuestNodesData)
	{
		if(QuestNodeData.NodeID==NodeDataToAdd.NodeID)
		{
			return false;
		}
	}
	CurrentQuestNodesData.Add(NodeDataToAdd);
	return true;
}

void UQuestManagerComponent::LogCurrentQuestNodesData()
{
	UE_LOG(LogTemp,Warning,TEXT("LogCurrentQuestNodesData-->Start,Num==%d"),CurrentQuestNodesData.Num());
	for(FQuestNodeData QuestNodeData:CurrentQuestNodesData)
	{
		UE_LOG(LogTemp,Warning,TEXT("Quest Node Id: %d"),QuestNodeData.NodeID);
		UE_LOG(LogTemp,Warning,TEXT("Quest Node QuestHintText: %s"),*QuestNodeData.QuestHintText);
		UE_LOG(LogTemp,Warning,TEXT("Quest Node QuestType: %d"),QuestNodeData.QuestType);
		
		for(FQuestCondition QuestCondition:QuestNodeData.Conditions)
		{
			UE_LOG(LogTemp,Warning,TEXT("Quest Node Condition:CurrentValue==%f NeededValue==%f itemID==%d DescriptionText==%s"),QuestCondition.CurrentValue,QuestCondition.NeededValue,QuestCondition.ItemID,*QuestCondition.DescriptionText);
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("LogCurrentQuestNodesData-->End"));
}

void UQuestManagerComponent::LogCurrentQuests()
{
	UE_LOG(LogTemp,Warning,TEXT("LogCurrentQuests-->Start,Num==%d"),CurrentQuests.Num());
	for(FQuestStructure QuestStructure:CurrentQuests)
	{
		UE_LOG(LogTemp,Warning,TEXT("Quest Id: %d"),QuestStructure.QuestID);
		UE_LOG(LogTemp,Warning,TEXT("Quest CurrentNodeID: %d"),QuestStructure.CurrentNodeID);
		for(FQuestNode QuestNode:QuestStructure.QuestNodes)
		{
			UE_LOG(LogTemp,Warning,TEXT("Quest NodeID:%d"),QuestNode.NodeID);
		}
		for(int endid:QuestStructure.EndNodeIDs)
		{
			UE_LOG(LogTemp,Warning,TEXT("Quest EndNodeID:%d"),endid);
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("LogCurrentQuests-->End"));
}

bool UQuestManagerComponent::CompleteQuest(int QuestId)
{
	for(int index=0;index<CurrentQuests.Num();index++)
	{
		if(CurrentQuests[index].QuestID==QuestId)
		{
			OnCompleteQuest(index);
			for(const auto& QuestNode:CurrentQuests[index].QuestNodes)//对于Quest中的每个节点，去CurrentQuestNodesData里找到对应的节点数据，并移除一次，因此数据要保证数据Id唯一
			{
				for(int NodeDataIndex=0;NodeDataIndex<CurrentQuestNodesData.Num();NodeDataIndex++)
				{
					if(CurrentQuestNodesData[NodeDataIndex].NodeID==QuestNode.NodeID)
					{
						CurrentQuestNodesData.RemoveAt(NodeDataIndex);
						break;
					}
				}
			}
			CurrentQuests.RemoveAt(index);
			return true;
		}
	}
	return false;
}
void UQuestManagerComponent::OnCompleteQuest(int index)
{
	TArray<FMyItemInfo> RewardsCopy=CurrentQuests[index].Rewards;
	int QuestId=CurrentQuests[index].QuestID;
	TArray<int> NextAccpetId=CurrentQuests[index].NextAcceptQuestId;
	
	AMyPlayer* Player=Cast<AMyPlayer>(GetOwner());
	Player->QuestRewards=RewardsCopy;
	Player->OnGetRewardsItems();

	FQuestStructure CompletedQuest=CurrentQuests[index];
	AddToCompletedQuestsWithoutRepeat(CompletedQuest);
	
	UE_LOG(LogTemp,Warning,TEXT("UQuestManagerComponent::OnCompleteQuest-->QuestId==%d"),QuestId);
	if(QuestId==1)
	{
		UMyGameInstance* MyGameInstance=Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		MyGameInstance->GameFlowKeyPointsInGameInstance[0]=true;
		if(MyGameInstance->SaveGameFlow())
		{
			UE_LOG(LogTemp,Warning,TEXT("GameFlowSaved"));
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("GameFlow Save Failed"));
		}
	}

	for(const auto& Id:NextAccpetId)
	{
		AcceptQuest(Id);
	}
	
}
bool UQuestManagerComponent::AddToCompletedQuestsWithoutRepeat(FQuestStructure StructureToAdd)
{
	bool bIsFind=false;
	for(const auto& Quest:CompletedQuests)
	{
		if(Quest.QuestID==StructureToAdd.QuestID)
		{
			bIsFind=true;
			break;
		}
	}
	if(bIsFind)
	{
		return false;
	}
	CompletedQuests.Add(StructureToAdd);
	return true;
}

bool UQuestManagerComponent::CheckQuestNodeCompleted(int QuestNodeID)
{
	for(const auto& QuestNodeData:CurrentQuestNodesData)
	{
		if(QuestNodeData.NodeID==QuestNodeID)
		{
			for(const auto& QuestCondition:QuestNodeData.Conditions)
			{
				if(QuestCondition.CurrentValue<QuestCondition.NeededValue||QuestCondition.CurrentValue==0)
				{
					return false;
				}
			}
			return true;//所有条件均CurrentValue>=NeededValue
		}
	}
	//没找到指定id返回false
	return false;
}


FQuestNodeData UQuestManagerComponent::GetQuestNodeDataByNodeID(int NodeID)
{
	for(const auto& QuestNodeData:CurrentQuestNodesData)
	{
		if(QuestNodeData.NodeID==NodeID)
		{
			return QuestNodeData;
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("GetQuestNodeDataByNodeID-Failed"));
	return FQuestNodeData();
}
FQuestNode UQuestManagerComponent::GetQuestNodeByNodeID(FQuestStructure Quest,int NodeID)
{
	for(FQuestNode QuestNode:Quest.QuestNodes)
	{
		if(QuestNode.NodeID==NodeID)
		{
			return QuestNode;
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("GetQuestNodeByNodeID-->Failed"));
	return FQuestNode();
}

bool UQuestManagerComponent::TryCommitQuestCurrentNode(int QuestId)
{
	for(auto& Quest:CurrentQuests)
	{
		if(Quest.QuestID==QuestId)
		{
			if(CheckQuestNodeCompleted(Quest.CurrentNodeID))
			{
				if(Quest.EndNodeIDs.Contains(Quest.CurrentNodeID))
				{
					UE_LOG(LogTemp,Warning,TEXT("TryCommitQuestCurrentNode-->Success!CompletedId: %d,QuestId:%d Completed"),Quest.CurrentNodeID,QuestId);
					CompleteQuest(QuestId);
					return true;
				}
				UE_LOG(LogTemp,Warning,TEXT("TryCommitQuestCurrentNode-->Success!CompletedId: %d"),Quest.CurrentNodeID);
				Quest.CurrentNodeID=GetQuestNodeByNodeID(Quest,Quest.CurrentNodeID).SuccessorNodeID;
				UE_LOG(LogTemp,Warning,TEXT("NextId: %d"),Quest.CurrentNodeID);
				return true;
			}
			
			UE_LOG(LogTemp,Warning,TEXT("TryCommitQuestCurrentNode-->Failed Because Check is False."));
			return false;
			
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("TryCommitQuestCurrentNode-->Failed Because QuestID is Not Found."));
	return false;
}


bool UQuestManagerComponent::LoadData()
{
	bool bIsSaveGameExist=UGameplayStatics::DoesSaveGameExist(FString("QuestSaveData"), 0);
	if(!bIsSaveGameExist)return false;
	UQuestSaveData*  LoadedQuestSaveData= Cast<UQuestSaveData>(UGameplayStatics::LoadGameFromSlot(FString("QuestSaveData"), 0));
	if(!LoadedQuestSaveData)return false;
	
	CurrentQuests=LoadedQuestSaveData->GetCurrentQuests();
	CurrentQuestNodesData=LoadedQuestSaveData->GetCurrentQuestNodesData();
	CompletedQuests=LoadedQuestSaveData->GetCompletedQuests();
	CurrentFollowQuestId=LoadedQuestSaveData->GetCurrentFollowQuestId();
	
	return true;
}
bool UQuestManagerComponent::SaveData()
{
	UQuestSaveData* Save = Cast<UQuestSaveData>(UGameplayStatics::CreateSaveGameObject(UQuestSaveData::StaticClass()));
	if (Save)
	{
		Save->SetCurrentQuests(CurrentQuests);
		Save->SetCurrentQuestNodesData(CurrentQuestNodesData);
		Save->SetCompletedQuests(CompletedQuests);
		Save->SetCurrentFollowQuestId(CurrentFollowQuestId);
		bool bIsSaveSuccess=UGameplayStatics::SaveGameToSlot(Save, FString("QuestSaveData"), 0);
		if(bIsSaveSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("UQuestManagerComponent-->Save Success"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UQuestManagerComponent-->Save Failed"));
		}
		return bIsSaveSuccess;
	}
	return false;
}

bool UQuestManagerComponent::CheckIsExistQuestById(int QuestId)const
{
	for(const auto& Quest:CurrentQuests)
	{
		if(Quest.QuestID==QuestId)
		{
			return true;
		}
	}
	return false;
}

bool UQuestManagerComponent::CheckIsExistQuestNodeDataById(int NodeId)const
{
	for(const auto& QuestNodeData:CurrentQuestNodesData)
	{
		if(QuestNodeData.NodeID==NodeId)
		{
			return true;
		}
	}
	return false;
}

bool UQuestManagerComponent::CheckIsExistQuestConditionByIndex(int NodeId,int index)const
{
	for(const auto& QuestNodeData:CurrentQuestNodesData)
	{
		if(QuestNodeData.NodeID==NodeId)
		{
			if(index<QuestNodeData.Conditions.Num()&&index>=0)
			{
				return true;
			}
			return false;
		}
	}
	return false;
}

bool UQuestManagerComponent::CheckIsCompletedQuestById(int QuestId)const
{
	for(const auto& Quest:CompletedQuests)
	{
		if(QuestId==Quest.QuestID)
		{
			return true;
		}
	}
	return false;
}

bool UQuestManagerComponent::ModQuestConditionValue(int QuestNodeId,int QuestConditionIndex,int Value)
{
	if(!(CheckIsExistQuestNodeDataById(QuestNodeId)&&CheckIsExistQuestConditionByIndex(QuestNodeId,QuestConditionIndex)))
	{
		return false;
	}
	int NodeDataIndex{GetQuestNodeDataIndexByNodeID(QuestNodeId)};
	CurrentQuestNodesData[NodeDataIndex].Conditions[QuestConditionIndex].CurrentValue+=Value;
	//UE_LOG(LogTemp,Warning,TEXT("QuestManagerComponent-->ModQuestConditionValue,Value=%f"),CurrentQuestNodesData[NodeDataIndex].Conditions[QuestConditionIndex].CurrentValue);
	return true;
}
TArray<int> UQuestManagerComponent::GetItemTypeQuestNodeInCurrentNode()const
{
	TArray<int> NodesId{};
	for(const auto& Quest:CurrentQuests)
	{
		if(CurrentQuestNodesData[GetQuestNodeDataIndexByNodeID(Quest.CurrentNodeID)].QuestType==EQuestType::Items)//若每个任务的当前节点类型等于Items
		{
			NodesId.AddUnique(Quest.CurrentNodeID);
		}
	}
	return NodesId;
}


TArray<int> UQuestManagerComponent::GetRelativeQuestNodeByItemId(TArray<int> ItemRelativeQuestNodes,int itemId)const
{
	TArray<int> NodesId{};
	for(const auto& NodeId:ItemRelativeQuestNodes)
	{
		for(const auto& QuestNodeData:CurrentQuestNodesData)
		{
			if(QuestNodeData.NodeID==NodeId)
			{
				//遍历当前节点的所有条件中是否存在指定itemid的条件
				for(const auto& Condition:QuestNodeData.Conditions)
				{
					if(Condition.ItemID==itemId)
					{
						NodesId.AddUnique(NodeId);
						break;
					}
				}
				break;
			}
		}
	}
	return NodesId;
}

bool UQuestManagerComponent::UpdateConditionAndTryCommit(int ItemId,int Value)
{
	TArray<int> ItemTypeNode{GetItemTypeQuestNodeInCurrentNode()};
	ItemTypeNode=GetRelativeQuestNodeByItemId(ItemTypeNode,ItemId);
	
	for(const auto& NodeId:ItemTypeNode)UE_LOG(LogTemp,Warning,TEXT("ItemTypeNode:id==%d"),NodeId);
	
	UE_LOG(LogTemp,Warning,TEXT("UpdateConditionAndTryCommit,1"));
	bool bIsModified=false;
	for(const auto& NodeId:ItemTypeNode )//1
	{
		int NodeDataIndex{GetQuestNodeDataIndexByNodeID(NodeId)};
		UE_LOG(LogTemp,Warning,TEXT("UpdateConditionAndTryCommit,2"));
		for(int index=0;index<CurrentQuestNodesData[NodeDataIndex].Conditions.Num();index++)
		{
			if(CurrentQuestNodesData[NodeDataIndex].Conditions[index].ItemID==ItemId)
			{
				if(ModQuestConditionValue(NodeId,index,Value))
				bIsModified=true;
				UE_LOG(LogTemp,Warning,TEXT("CurrentQuestNodesData[%d].Conditions[%d].ItemID==%d,CurrentValue==%f"),NodeDataIndex,index,CurrentQuestNodesData[NodeDataIndex].Conditions[index].ItemID,CurrentQuestNodesData[NodeDataIndex].Conditions[index].CurrentValue);
			}
		}
		UE_LOG(LogTemp,Warning,TEXT("UpdateConditionAndTryCommit,3"));
		for(const auto& Quest:CurrentQuests)
		{
			if(Quest.CurrentNodeID==NodeId)
			{
				TryCommitQuestCurrentNode(Quest.QuestID);
				break;//要保证唯一任务包含此节点，不可继续遍历，TryCommit函数里的Complete函数会修改CurrentQuest
			}
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("UpdateConditionAndTryCommit,4"));
	return bIsModified;
}

bool UQuestManagerComponent::CommonUpdateConditionAndTryCommit(int QuestId,int ConditionIndex,int Value)
{
	bool bIsModified=false;
	for(const auto& Quest:CurrentQuests)
	{
		if(Quest.QuestID==QuestId)
		{
			if(ModQuestConditionValue(Quest.CurrentNodeID,ConditionIndex,Value))
				bIsModified=true;
			break;
		}
	}
	TryCommitQuestCurrentNode(QuestId);
	return bIsModified;
}


int UQuestManagerComponent::GetQuestNodeDataIndexByNodeID(int NodeID)const
{
	int index{0};
	for(;index<CurrentQuestNodesData.Num();index++)
	{
		if(CurrentQuestNodesData[index].NodeID==NodeID)
		{
			return index;
		}
	}
	return index;
}

bool UQuestManagerComponent::OnFollow(const int QuestId)//相当于加了判断的set
{
	if(CheckIsExistQuestById(QuestId))
	{
		CurrentFollowQuestId=QuestId;
		SaveData();
		return true;
	}
	return false;
}

int UQuestManagerComponent::GetCurrentFollowQuestId()
{
	return CurrentFollowQuestId;
}

FQuestStructure UQuestManagerComponent::GetFollowQuestStructure()const
{
	return GetQuestStructureById(CurrentFollowQuestId);
}

FQuestStructure UQuestManagerComponent::GetQuestStructureById(const int QuestId)const
{
	for(const auto& Quest:CurrentQuests)
	{
		if(Quest.QuestID==QuestId)
		{
			return Quest;
		}
	}
	return FQuestStructure();
}	
