// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogManager.h"

#include "DialogHUD.h"

void UDialogManager::AssignDialogHUD(UDialogHUD* NewHUD)
{
	DialogHUD = NewHUD;
}

void UDialogManager::TriggerDialog(FDialogStruct InitialDialog, UDialogComponent* NewComponent)
{
	DialogHUD->BeginConversation(InitialDialog);
	DialogHUD->SetVisibility(ESlateVisibility::Visible);
	CurrentComponent = NewComponent;
}

void UDialogManager::TriggerAction(EDialogAction DialogAction)
{
	CurrentComponent->TriggerDialogAction(DialogAction);
}


