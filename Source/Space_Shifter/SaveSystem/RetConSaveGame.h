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
	FName ActorName;

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

/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API URetConSaveGame : public USaveGame
{
	GENERATED_BODY()

public:	

	UPROPERTY()
	FPlayerSaveData PlayerSave;

	UPROPERTY()
	TMap<FName, FActorSaveData> SavedActorMap;
	
};
