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
	LineOptions = DialogComponent->GetViableLines(DialogComponent->GetLineGroup(CurrentCharacter->CharacterName, ELineGroup::General));
	DisplayDialog();
}

bool UDialogHUD::NextLine()
{
	const FDialogLine* CurrentLine = LineOptions[CurrentDialog];
	if (CurrentLine->KnowledgeResults.Num() != 0)
	{
		for (const EKnowledge Knowledge : CurrentLine->KnowledgeResults)
		{
			GetGameInstance()->GetSubsystem<UQuestManager>()->GetKnowledge(Knowledge);
		}
	}
	if (CurrentLine->LevelActionResults.Num() != 0)
	{
		for (const ELevelAction LevelAction : LineOptions[CurrentDialog]->LevelActionResults)
		{
			GetGameInstance()->GetSubsystem<UDialogManager>()->TriggerAction(LevelAction);
		}
	}
	if (CurrentLine->SceneChangeResult != EScene::SceneDefault)
	{
		Cast<AShifterGamemode>(UGameplayStatics::GetGameMode(this))->ChangeScene(CurrentLine->SceneChangeResult);
	}
	if (CurrentLine->bLeave)
	{
		return false;
	}
	LineOptions.Empty();
	CurrentCharacter = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UQuestManager>()->GetCharacterStruct(CurrentLine->NextCharacter);
	LineOptions = DialogComponent->GetViableLines(DialogComponent->GetLineGroup(CurrentCharacter->CharacterName, CurrentLine->NextLineGroup));
	ensure(LineOptions.Num() != 0);
	DisplayDialog();
	return true;
}
