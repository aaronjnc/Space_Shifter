// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RetConSaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSaveTimeDelegate, int, SaveNum);

static const FString GGameSaveLocation = "_GameSave";
static const FString GTravelPoint = "_TravelSave";
static const FString GSavePoint = "_SavePoint";

/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API USaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:

	FString CurrentSaveSlot;

	UPROPERTY()
	URetConSaveGame* CurrentSaveGame;

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void SaveGame();

	UFUNCTION()
	void SaveEnvironment(const FString& SaveName);

	UFUNCTION()
	void SavePlayer();

	UFUNCTION()
	void LoadSave();
};
