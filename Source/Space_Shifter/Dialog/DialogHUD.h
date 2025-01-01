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
	UTextBlock* DialogTextBox;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TMap<TEnumAsByte<ECharacterName>, FDataTableRowHandle> CharacterMap;

	UDataTable* DialogTree;

	TArray<FDialogLine*> DialogOptions;

	FDialogLine* CurrentDialog;

	FCharacterStruct* CurrentCharacter;

public:

	void DisplayDialog() const;

	void BeginConversation(FCharacterStruct* NewCharacter, UDataTable* NewDialogTree);

	bool NextLine();
	
};
