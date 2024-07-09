// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogHUD.h"
#include "DialogComponent.h"
#include "DialogManager.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UDialogHUD::DisplayDialog()
{
	FCharacterStruct TalkingCharacter = *CharacterMap[CurrentDialog.Character].GetRow<FCharacterStruct>("");
	if (CurrentDialog.Character == ECharacterName::Player)
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
	DialogTextBox->SetText(CurrentDialog.Sentence);
}

void UDialogHUD::BeginConversation(FDialogStruct InitialDialog)
{
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
