// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RetConSaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSaveTimeDelegate, int, SaveNum);

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

	UFUNCTION()
	void WriteSave();

	UFUNCTION()
	void LoadSave();
};
