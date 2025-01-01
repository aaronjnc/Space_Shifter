// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Space_Shifter/Interactables/InteractableInterface.h"
#include "Space_Shifter/SupporterClass.h"
#include "DialogComponent.generated.h"

class UQuestManager;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACE_SHIFTER_API UDialogComponent : public UActorComponent, public IInteractableInterface
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TMap<TEnumAsByte<ELevelAction>, TObjectPtr<AActor>> SentenceDialogActions;
	UPROPERTY(EditAnywhere, Category = "Dialog")
	TEnumAsByte<enum ECharacterName> CharacterEnum;
	UPROPERTY(EditAnywhere, Category = "Dialog")
	UDataTable* DialogTree;
	FCharacterStruct* CharacterStruct;
	TMap<TEnumAsByte<ELineGroup>, TArray<const FDialogLine*>> LineGroupLinks;
	UPROPERTY()
	UQuestManager* QuestManager;

public:	
	// Sets default values for this component's properties
	UDialogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual EMappingContexts Interact() override;

	virtual EMappingContexts StopInteract() override;

	void TriggerDialogAction(ELevelAction DialogAction);

	TArray<const FDialogLine*> GetLineGroup(ELineGroup NewLineGroup);

	TArray<const FDialogLine*> GetViableLines(TArray<const FDialogLine*> DialogLines);
	
};
