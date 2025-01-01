// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogComponent.h"
#include "Space_Shifter/SupporterClass.h"
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

	TWeakObjectPtr<UDialogComponent> CurrentComponent;

public:

	void AssignDialogHUD(UDialogHUD* NewHUD);

	void TriggerDialog(FCharacterStruct* CurrentCharacter, UDataTable* DialogTree, UDialogComponent* NewComponent);

	void TriggerAction(const ELevelAction DialogAction) const;
};
