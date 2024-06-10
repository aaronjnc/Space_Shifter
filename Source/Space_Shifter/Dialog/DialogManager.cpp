// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogManager.h"

#include "DialogHUD.h"

void UDialogManager::AssignDialogHUD(UDialogHUD* NewHUD)
{
	DialogHUD = NewHUD;
}

void UDialogManager::TriggerDialog(FDialogStruct InitialDialog)
{
	DialogHUD->BeginConversation(InitialDialog);
	DialogHUD->SetVisibility(ESlateVisibility::Visible);
}
