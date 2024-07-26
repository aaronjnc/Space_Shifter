// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "Kismet/GameplayStatics.h"

FQuestStruct* UQuestManager::GetQuest(const int& QuestNum)
{
	TArray<FQuestStruct*> AllQuests;
	QuestDataTable->GetAllRows("", AllQuests);
	return AllQuests[QuestNum];
}

void UQuestManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	QuestDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTableLocation));
	if (!QuestDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to load data table"));
		return;
	}
	//LoadQuest(0);
}

void UQuestManager::NextQuest()
{
	LoadQuest(CurrentQuestNum + 1);
}

void UQuestManager::LoadQuest(const int& QuestNum)
{
	CurrentQuestNum = QuestNum;
	CurrentQuest = GetQuest(CurrentQuestNum);
	UE_LOG(LogTemp, Warning, TEXT("Load Level"));
	LoadLevel(0);
}

void UQuestManager::NextLevel()
{
	LoadLevel(CurrentLevelNum + 1);
}

void UQuestManager::LoadLevel(const int& LevelNum)
{
	CurrentLevelNum = LevelNum;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, CurrentQuest->SceneOrder[CurrentLevelNum]);
}
