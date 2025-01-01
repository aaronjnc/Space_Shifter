// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogComponent.h"
#include "Blueprint/UserWidget.h"
#include "DialogHUD.generated.h"

/**
 * 
 */
class UImage;
class UTextBlock;
class UDialogComponent;
struct FDialogLine;
struct FCharacterStruct;
enum ECharacterName;
UCLASS()
class SPACE_SHIFTER_API UDialogHUD : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerPicture;

	UPROPERTY(meta = (BindWidget))
	UImage* NPCPicture;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameTextBox;
	
	UPROPERTY(meta = (BindWidget))
	TArray<UTextBlock*> DialogTextBoxes;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TMap<TEnumAsByte<ECharacterName>, FDataTableRowHandle> CharacterMap;

	UPROPERTY()
	UDialogComponent* DialogComponent;

	TArray<FDialogLine*> DialogOptions;

	TArray<const FDialogLine*> LineOptions;

	int CurrentDialog = 0;

	FCharacterStruct* CurrentCharacter;

public:

	void DisplayDialog() const;

	void BeginConversation(FCharacterStruct* NewCharacter, UDialogComponent* NewDialogComponent);

	bool NextLine();
	
};
