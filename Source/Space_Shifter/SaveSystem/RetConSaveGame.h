// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RetConSaveGame.generated.h"

USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FString ActorName;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	TArray<uint8> ByteData;
	
};

USTRUCT()
struct FPlayerSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	TArray<uint8> ByteData;
};

USTRUCT()
struct FPlayerComponentSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<uint8> ByteData;
};

UCLASS()
class SPACE_SHIFTER_API URetConEnvironmentSave : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TMap<FName, FActorSaveData> SavedActorMap;
};

UCLASS()
class SPACE_SHIFTER_API URetConPlayerSave : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FPlayerSaveData PlayerSave;

	UPROPERTY()
	TMap<FString, FPlayerComponentSaveData> PlayerComponents;
};

/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API URetConSaveGame : public USaveGame
{
	GENERATED_BODY()

public:	

	UPROPERTY()
	TArray<int> SaveSlots;
	
	//Level Progress
	
};

UCLASS()
class SPACE_SHIFTER_API UUserSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	int AchievementsFound = 0;
	//Settings
	//Achievements
};
