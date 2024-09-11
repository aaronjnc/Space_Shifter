// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Space_Shifter/Dialog/DialogComponent.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestManager.generated.h"

static FString DataTableLocation = "/Game/Space_Shifter/Resources/DataTables/DT_QuestList";

USTRUCT(BlueprintType)
struct FSceneStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> QuestScene;

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
};

USTRUCT(BlueprintType)
struct FQuestStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FString QuestName;

	UPROPERTY(EditAnywhere)
	TArray<FDataTableRowHandle> SceneOrder;
};


struct FCutsceneStruct;
class ULevelSequence;
/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API UQuestManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:

	int CurrentQuestNum = 0;

	int CurrentSceneNum = 0;

	FSceneStruct* CurrentScene;

	FCutsceneStruct* CutsceneStruct;

	FQuestStruct* CurrentQuestList;
	
	TObjectPtr<UDataTable> QuestListDataTable;

	bool bIsCutscene = false;

	TMap<ECharacterName, FCharacterStruct> CharacterStructs;

private:

	FQuestStruct* GetQuest(const int& QuestNum) const;

	void UpdateScene(const int& SceneNum);

	void UpdateCharacters();

protected:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:

	void NextQuest();

	void LoadQuest(const int& QuestNum);

	void NextScene();

	void LoadScene(const int& LevelNum);
	
	ULevelSequence* GetCutscene() const;

	FCharacterStruct GetCharacterStruct(const ECharacterName CharacterName);
	
};
