// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogHUD.h"

#include "DialogManager.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Space_Shifter/SupporterClass.h"
#include "Space_Shifter/GameStructure/QuestManager.h"
#include "Space_Shifter/GameStructure/ShifterGamemode.h"

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
	for (int i = 0; i < 3; i++)
	{
		UTextBlock* TextBlock;
		switch (i)
		{
			default:
			case 0:
				TextBlock = DialogTextBox1;
				break;
			case 1:
				TextBlock = DialogTextBox2;
				break;
			case 2:
				TextBlock = DialogTextBox3;
				break;
		}
		if (LineOptions.Num() > i)
		{
			TextBlock->SetText(LineOptions[i]->Text);
			TextBlock->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			TextBlock->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UDialogHUD::BeginConversation(FCharacterStruct* NewCharacter, UDialogComponent* NewDialogComponent)
{
	CurrentCharacter = NewCharacter;
	DialogComponent = NewDialogComponent;
	DisplayDialog();
}

bool UDialogHUD::NextLine()
{
	if (LineOptions[CurrentDialog]->KnowledgeResults.Num() != 0)
	{
		for (const EKnowledge Knowledge : LineOptions[CurrentDialog]->KnowledgeResults)
		{
			GetGameInstance()->GetSubsystem<UQuestManager>()->GetKnowledge(Knowledge);
		}
	}
	if (LineOptions[CurrentDialog]->LevelActionResults.Num() != 0)
	{
		for (const ELevelAction LevelAction : LineOptions[CurrentDialog]->LevelActionResults)
		{
			GetGameInstance()->GetSubsystem<UDialogManager>()->TriggerAction(LevelAction);
		}
	}
	if (LineOptions[CurrentDialog]->SceneChangeResult)
	{
		Cast<AShifterGamemode>(UGameplayStatics::GetGameMode(this))->ChangeScene(LineOptions[CurrentDialog]->SceneChangeResult);
	}
	if (LineOptions[CurrentDialog]->bLeave)
	{
		return false;
	}
	LineOptions.Empty();
	LineOptions = DialogComponent->GetViableLines(DialogComponent->GetLineGroup(LineOptions[CurrentDialog]->NextLineGroup));
	ensure(LineOptions.Num() != 0);
	DisplayDialog();
	return true;
}
