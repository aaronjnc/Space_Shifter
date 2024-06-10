// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogHUD.h"
#include "DialogComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UDialogHUD::BeginConversation(FDialogStruct InitialDialog)
{
	FCharacterStruct TalkingCharacter = *CharacterMap[InitialDialog.Character].GetRow<FCharacterStruct>("");
	if (InitialDialog.Character == ECharacterName::Player)
	{
		PlayerPicture->SetVisibility(ESlateVisibility::Visible);
		NPCPicture->SetVisibility(ESlateVisibility::Hidden);
		PlayerPicture->SetBrushFromTexture(TalkingCharacter.CharacterPortrait);
	}
	else
	{
		NPCPicture->SetVisibility(ESlateVisibility::Visible);
		PlayerPicture->SetVisibility(ESlateVisibility::Hidden);
		NPCPicture->SetBrushFromTexture(TalkingCharacter.CharacterPortrait);
	}
	NameTextBox->SetText(TalkingCharacter.CharacterName);
	DialogTextBox->SetText(InitialDialog.Sentence);
}
