// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestManager.generated.h"

static FString DataTableLocation = "/Game/Space_Shifter/Resources/DataTables/DT_Quests";

USTRUCT(BlueprintType)
struct FQuestStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString QuestName;

	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UWorld>> SceneOrder;

	UPROPERTY(EditAnywhere)
	UDataTable* DialogDataTable;
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

	int CurrentLevelNum = 0;

	FQuestStruct* CurrentQuest;
	
	TObjectPtr<UDataTable> QuestDataTable;

private:

	FQuestStruct* GetQuest(const int& QuestNum);

protected:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:

	void NextQuest();

	void LoadQuest(const int& QuestNum);

	void NextLevel();

	void LoadLevel(const int& LevelNum);
	
};
