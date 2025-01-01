// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SupporterClass.generated.h"

class ULevelSequence;

UENUM(BlueprintType)
enum ECharacterName
{
	Player,
	Dave,
};

UENUM(BlueprintType)
enum ELevelAction
{
	Destroy,
};

UENUM(BlueprintType)
enum EScene
{
	SceneDefault,
};

UENUM(BlueprintType)
enum ELineGroup
{
	General,
	One,
	Two,
	Three,
	Four,
	NextLine_Max UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ELineGroup, ELineGroup::NextLine_Max);


UENUM(BlueprintType)
enum EKnowledge
{
	KnowledgeDefault,
	Knowledge_Max UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EKnowledge, EKnowledge::Knowledge_Max);

UENUM(BlueprintType)
enum ECutsceneTag
{
	 CutsceneDefault,
};

UENUM(BlueprintType)
enum ESceneType
{
	Cutscene,
	Puzzle,
};

USTRUCT(BlueprintType)
struct FCharacterStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECharacterName> CharacterName;

	UPROPERTY(EditAnywhere)
	UTexture2D* CharacterProfile;

	UPROPERTY(EditAnywhere)
	FString CharacterNameString;
};

USTRUCT(BlueprintType)
struct FDialogLine : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ELineGroup> LineGroup;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EKnowledge>> Prerequisites;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EKnowledge>> Disqualifiers;

	UPROPERTY(EditAnywhere)
	FText Text;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle Speaker;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<ELevelAction>> LevelActionResults;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EScene> SceneChangeResult;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EKnowledge>> KnowledgeResults;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ELineGroup> NextLineGroup;

	UPROPERTY(EditAnywhere)
	bool bLeave;
};

USTRUCT(BlueprintType)
struct FCutsceneStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	ULevelSequence* CutsceneVideo;

	UPROPERTY(EditAnywhere)
	UDataTable* DialogTable;
};

USTRUCT(BlueprintType)
struct FSceneStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESceneType> SceneType;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle Cutscene;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle NextScene;
};

USTRUCT(BlueprintType)
struct FQuestStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FString QuestName;

	UPROPERTY(EditAnywhere)
	TArray<FDataTableRowHandle> SceneList;
};

/**
 * 
 */
class SPACE_SHIFTER_API SupporterClass
{
public:
	SupporterClass();
	~SupporterClass();
};
