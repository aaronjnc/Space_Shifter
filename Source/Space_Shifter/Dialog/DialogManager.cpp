// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogManager.h"

#include "DialogHUD.h"

void UDialogManager::AssignDialogHUD(UDialogHUD* NewHUD)
{
	DialogHUD = NewHUD;
}

void UDialogManager::TriggerDialog(const FCharacterStruct CurrentCharacter, const FDialogStruct InitialDialog, UDialogComponent* NewComponent)
{
	DialogHUD->BeginConversation(CurrentCharacter, InitialDialog);
	DialogHUD->SetVisibility(ESlateVisibility::Visible);
	CurrentComponent = NewComponent;
}

void UDialogManager::TriggerAction(const EDialogAction DialogAction) const
{
	CurrentComponent->TriggerDialogAction(DialogAction);
}


