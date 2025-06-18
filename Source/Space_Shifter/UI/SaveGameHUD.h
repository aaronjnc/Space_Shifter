// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "SaveGameHUD.generated.h"

class UListView;
class UTextBlock;
class UImage;
class UEditableTextBox;
class UComboBoxString;
/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API USaveGameHUD : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UEditableTextBox* NewSaveName;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UComboBoxString* NewDifficulty;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* CreateSave;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* Clear;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* DeleteSave;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* StartGame;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UListView* SaveList;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* CurrentLevel;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* Difficulty;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* PlayTime;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* FirstSave;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* LastSave;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* SaveName;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UImage* SaveImage;

	UPROPERTY()
	UWorld* WorldRef;

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void SelectSave(UObject* Item);

	UFUNCTION()
	void CreateGame();

	UFUNCTION()
	void LoadGame();

	UFUNCTION()
	void DeleteGame();

private:

	void UpdateSaveList() const;

};
