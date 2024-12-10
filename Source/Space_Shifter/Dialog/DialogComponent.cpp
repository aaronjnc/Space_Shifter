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

