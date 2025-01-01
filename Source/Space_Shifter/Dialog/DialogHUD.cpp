// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogHUD.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Space_Shifter/SupporterClass.h"

void UDialogHUD::DisplayDialog() const
{
	if (CurrentCharacter->CharacterName == ECharacterName::Player)
	{
		PlayerPicture->SetVisibility(ESlateVisibility::Visible);
		NPCPicture->SetVisibility(ESlateVisibility::Hidden);
		PlayerPicture->SetBrushFromTexture(CurrentCharacter->CharacterProfile);
	}
	else
	{
		NPCPicture->SetVisibility(ESlateVisibility::Visible);
		PlayerPicture->SetVisibility(ESlateVisibility::Hidden);
		NPCPicture->SetBrushFromTexture(CurrentCharacter->CharacterProfile);
	}
	NameTextBox->SetText(FText::FromString(CurrentCharacter->CharacterNameString));
	DialogTextBox->SetText(CurrentDialog->Text);
}

void UDialogHUD::BeginConversation(FCharacterStruct* NewCharacter, UDataTable* NewDialogTree)
{
	CurrentCharacter = NewCharacter;
	DialogTree = NewDialogTree;
	DisplayDialog();
}

bool UDialogHUD::NextLine()
{
	/*if (CurrentDialog->SentenceDialogEnums.Num() != 0)
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
	DisplayDialog();*/
	return true;
}
