// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RetConSaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameSubsystem.generated.h"

static const FString GGameSaveLocation = "_GameSave";
static const FString GTimeSlotSave = "_TimeSlot_";
static const FString GLevelSave = "_CurrentLevel";
static const FString GPlayerSave = "_PlayerSave";
static const FString GSystemSave = "System_Save";

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

	UPROPERTY()
	URetConEnvironmentSave* CurrentEnvironmentSave;

	UPROPERTY()
	URetConPlayerSave* CurrentPlayerSave;

public:

	void CreateNewSave(const FString& SaveName);

	void DeleteSave(const FString& SaveName);

	TArray<FString> GetSaves();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void SaveGame();

	UFUNCTION()
	void SaveEnvironment(const FString& SaveName);

	UFUNCTION()
	void SavePlayer();

	UFUNCTION()
	void LoadSave(const FString& SaveName);

	UFUNCTION()
	void LoadEnvironment(const FString& SaveName);

	static FString GetSavePath(const FString& SaveName, const FString& SaveType);
};
