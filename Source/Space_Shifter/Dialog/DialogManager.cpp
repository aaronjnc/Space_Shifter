// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogManager.h"

#include "DialogHUD.h"

void UDialogManager::AssignDialogHUD(UDialogHUD* NewHUD)
{
	DialogHUD = NewHUD;
}

void UDialogManager::TriggerDialog(FCharacterStruct* CurrentCharacter, UDataTable* DialogTree, UDialogComponent* NewComponent)
{
	DialogHUD->BeginConversation(CurrentCharacter, DialogTree);
	DialogHUD->SetVisibility(ESlateVisibility::Visible);
	CurrentComponent = NewComponent;
}

void UDialogManager::TriggerAction(const ELevelAction DialogAction) const
{
	CurrentComponent->TriggerDialogAction(DialogAction);
}


