// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "SaveSlotHUD.generated.h"

class USaveInformationSave;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API USaveSlotHUD : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* SaveName;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* CurrentLevel;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* SaveTime;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* LastSave;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UImage* SaveImage;

	UPROPERTY()
	USaveInformationSave* SaveSlot;

public:

	void SetupSaveSlot(USaveInformationSave* SaveGame);

	USaveInformationSave* GetSaveSlot() const;
};
