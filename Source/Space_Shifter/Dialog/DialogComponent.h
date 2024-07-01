// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogActionInterface.h"
#include "Components/ActorComponent.h"
#include "Space_Shifter/Interactables/InteractableInterface.h"
#include "DialogComponent.generated.h"

UENUM(BlueprintType)
enum EDialogAction
{
	DefaultAction,
	Destroy,
};

UENUM(BlueprintType)
enum ECharacterName
{
	Player,
	Dave,
};

USTRUCT(BlueprintType)
struct FCharacterStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CharacterPortrait;
};

USTRUCT(BlueprintType)
struct FDialogStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECharacterName> Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EDialogAction>> SentenceDialogEnums;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Sentence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle NextSentence;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACE_SHIFTER_API UDialogComponent : public UActorComponent, public IInteractableInterface
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TMap<TEnumAsByte<EDialogAction>, IDialogActionInterface*> SentenceDialogActions;
	UPROPERTY(EditAnywhere, Category = "Dialog")
	FDataTableRowHandle DialogStruct;

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

	void TriggerDialogAction(EDialogAction DialogAction);
	
};
