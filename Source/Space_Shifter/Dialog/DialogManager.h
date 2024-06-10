// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogComponent.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialogManager.generated.h"

/**
 * 
 */
class UDialogHUD;
UCLASS()
class SPACE_SHIFTER_API UDialogManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:

	TWeakObjectPtr<UDialogHUD> DialogHUD;

public:

	void AssignDialogHUD(UDialogHUD* NewHUD);

	void TriggerDialog(FDialogStruct InitialDialog);
};
