// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestManager.generated.h"

static FString DataTableLocation = "/Game/Space_Shifter/Resources/DataTables/DT_Quests";

USTRUCT(BlueprintType)
struct FSceneStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> QuestScene;

	UPROPERTY(EditAnywhere)
	UDataTable* DialogDataTable;
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

	FQuestStruct* CurrentQuestList;
	
	TObjectPtr<UDataTable> QuestListDataTable;

private:

	FQuestStruct* GetQuest(const int& QuestNum) const;

	FSceneStruct* GetScene(const int& SceneNum) const;

protected:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:

	void NextQuest();

	void LoadQuest(const int& QuestNum);

	void NextScene();

	void LoadScene(const int& LevelNum);
	
};
