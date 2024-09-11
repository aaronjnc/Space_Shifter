// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "Kismet/GameplayStatics.h"
#include "Space_Shifter/Cutscenes/CutsceneManager.h"

FQuestStruct* UQuestManager::GetQuest(const int& QuestNum) const
{
	TArray<FQuestStruct*> AllQuests;
	QuestListDataTable->GetAllRows("", AllQuests);
	return AllQuests[QuestNum];
}

void UQuestManager::UpdateScene(const int& SceneNum)
{
	bIsCutscene = true;
	CutsceneStruct = CurrentQuestList->SceneOrder[SceneNum].GetRow<FCutsceneStruct>("");
	CurrentScene = CurrentQuestList->SceneOrder[SceneNum].GetRow<FSceneStruct>("");
	if (!CutsceneStruct)
	{
		bIsCutscene = false;
	}
}

void UQuestManager::UpdateCharacters()
{
	CharacterStructs.Empty();
	const UDataTable* CharacterTable = CurrentScene->CharacterDataTable;
	for (const FName CharacterName : CharacterTable->GetRowNames())
	{
		const FCharacterStruct* CharacterStruct = CharacterTable->FindRow<FCharacterStruct>(CharacterName, "");
		CharacterStructs.Add(CharacterStruct->Character, *CharacterStruct);
	}
}

void UQuestManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	QuestListDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTableLocation));
	if (!QuestListDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to load data table at %s"), *DataTableLocation);
		return;
	}
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
	UpdateScene(LevelNum);
	CurrentSceneNum = LevelNum;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, CurrentScene->QuestScene);
}

ULevelSequence* UQuestManager::GetCutscene() const
{
	return CutsceneStruct->CutsceneVideo;
}

FCharacterStruct UQuestManager::GetCharacterStruct(const ECharacterName CharacterName)
{
	return CharacterStructs[CharacterName];
}
