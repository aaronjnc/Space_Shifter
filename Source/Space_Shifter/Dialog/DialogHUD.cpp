// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogHUD.h"
#include "DialogComponent.h"
#include "DialogManager.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UDialogHUD::DisplayDialog() const
{
	if (CurrentCharacter.Character == ECharacterName::Player)
	{
		PlayerPicture->SetVisibility(ESlateVisibility::Visible);
		NPCPicture->SetVisibility(ESlateVisibility::Hidden);
		PlayerPicture->SetBrushFromTexture(CurrentCharacter.CharacterPortrait);
	}
	else
	{
		NPCPicture->SetVisibility(ESlateVisibility::Visible);
		PlayerPicture->SetVisibility(ESlateVisibility::Hidden);
		NPCPicture->SetBrushFromTexture(CurrentCharacter.CharacterPortrait);
	}
	NameTextBox->SetText(CurrentCharacter.CharacterName);
	DialogTextBox->SetText(CurrentDialog.Sentence);
}

void UDialogHUD::BeginConversation(const FCharacterStruct NewCharacter, const FDialogStruct InitialDialog)
{
	CurrentCharacter = NewCharacter;
	CurrentDialog = InitialDialog;
	DisplayDialog();
}

bool UDialogHUD::NextLine()
{
	if (CurrentDialog.SentenceDialogEnums.Num() != 0)
	{
		for (const EDialogAction DialogAction : CurrentDialog.SentenceDialogEnums)
		{
			GetGameInstance()->GetSubsystem<UDialogManager>()->TriggerAction(DialogAction);
		}
	}
	if (CurrentDialog.NextSentence.IsNull())
	{
		return false;
	}
	CurrentDialog = *CurrentDialog.NextSentence.GetRow<FDialogStruct>("");
	DisplayDialog();
	return true;
}
