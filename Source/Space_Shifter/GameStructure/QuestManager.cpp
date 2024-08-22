// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "Kismet/GameplayStatics.h"

FQuestStruct* UQuestManager::GetQuest(const int& QuestNum) const
{
	TArray<FQuestStruct*> AllQuests;
	QuestListDataTable->GetAllRows("", AllQuests);
	return AllQuests[QuestNum];
}

FSceneStruct* UQuestManager::GetScene(const int& SceneNum) const
{
	return CurrentQuestList->SceneOrder[SceneNum].GetRow<FSceneStruct>("");
}

void UQuestManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	QuestListDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTableLocation));
	if (!QuestListDataTable)
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
	CurrentQuestList = GetQuest(CurrentQuestNum);
	CurrentSceneNum = 0;
	UE_LOG(LogTemp, Warning, TEXT("Load Level"));
	LoadScene(0);
}

void UQuestManager::NextScene()
{
	LoadScene(CurrentSceneNum + 1);
}

void UQuestManager::LoadScene(const int& LevelNum)
{
	CurrentScene = GetScene(LevelNum);
	CurrentSceneNum = LevelNum;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, CurrentScene->QuestScene);
}
