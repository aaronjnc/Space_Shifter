// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogComponent.h"

#include "DialogManager.h"
#include "Kismet/GameplayStatics.h"
#include "DialogActionInterface.h"
#include "Space_Shifter/GameStructure/QuestManager.h"

// Sets default values for this component's properties
UDialogComponent::UDialogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogComponent::BeginPlay()
{
	Super::BeginPlay();

	QuestManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UQuestManager>();
	CharacterStruct = QuestManager->GetCharacterStruct(CharacterEnum);
	UE_LOG(LogTemp, Warning, TEXT("Character Name: %s"), *CharacterStruct->CharacterNameString);
	checkf(DialogTree != nullptr, TEXT("Invalid dialog tree on object %s"), *GetOwner()->GetName());
	for (const TPair<FName, uint8*> RowItr : DialogTree->GetRowMap())
	{
		const FDialogLine* DialogLine = reinterpret_cast<const FDialogLine*>(RowItr.Value);
		if (!LineGroupLinks.Contains(DialogLine->Speaker))
		{
			LineGroupLinks.Add(DialogLine->Speaker, TMap<TEnumAsByte<ELineGroup>, TArray<const FDialogLine*>>());
		}
		if (!LineGroupLinks[DialogLine->Speaker].Contains(DialogLine->LineGroup))
		{
			LineGroupLinks[DialogLine->Speaker].Add(DialogLine->LineGroup, TArray<const FDialogLine*>());
		}
		LineGroupLinks[DialogLine->Speaker][DialogLine->LineGroup].Add(DialogLine);
	}
}


// Called every frame
void UDialogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EMappingContexts UDialogComponent::Interact()
{
	UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UDialogManager>()->TriggerDialog(CharacterStruct, DialogTree, this);
	return EMappingContexts::Dialog;
}

EMappingContexts UDialogComponent::StopInteract()
{
	return EMappingContexts::DefaultContext;
}

void UDialogComponent::TriggerDialogAction(ELevelAction DialogAction)
{
	IDialogActionInterface* ActionInterface = Cast<IDialogActionInterface>(SentenceDialogActions[DialogAction]);
	if (ActionInterface)
	{
		ActionInterface->PerformDialogAction();
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Actor %s does not implement IDialogActionInterface."), *SentenceDialogActions[DialogAction]->GetName());
	}
}

TArray<const FDialogLine*> UDialogComponent::GetLineGroup(ECharacterName Speaker, ELineGroup NewLineGroup)
{
	return LineGroupLinks[Speaker][NewLineGroup];
}

TArray<const FDialogLine*> UDialogComponent::GetViableLines(TArray<const FDialogLine*> DialogLines) const
{
	TArray<const FDialogLine*> ViableLines;
	for (int i = 0; i < DialogLines.Num(); i++)
	{
		bool bValid = true;
		for (const EKnowledge Prerequisite : DialogLines[i]->Prerequisites)
		{
			if (!QuestManager->HasKnowledge(Prerequisite))
			{
				bValid = false;
				break;
			}
		}
		if (bValid)
		{
			for (const EKnowledge Disqualify : DialogLines[i]->Disqualifiers)
			{
				if (QuestManager->HasKnowledge(Disqualify))
				{
					bValid = false;
					break;
				}
			}
		}
		if (bValid)
		{
			UE_LOG(LogTemp, Warning, TEXT("Valid Line: %s"), *DialogLines[i]->Text.ToString());
			ViableLines.Add(DialogLines[i]);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid Line: %s"), *DialogLines[i]->Text.ToString());
		}
	}
	ensure(DialogLines.Num() <= 3);
	return ViableLines;
}

