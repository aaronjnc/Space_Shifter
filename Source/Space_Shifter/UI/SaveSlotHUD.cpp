// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSlotHUD.h"

#include "Components/Image.h"
#include "Space_Shifter/SaveSystem/RetConSaveGame.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void USaveSlotHUD::SetupSaveSlot(USaveInformationSave* SaveGame)
{
	SaveSlot = SaveGame;
	if (!SaveSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Save Slot"));
		return;
	}
	SaveName->SetText(FText::FromString(SaveGame->SaveName));
	CurrentLevel->SetText(FText::FromString(UEnum::GetValueAsString(SaveGame->CurrentLevel.GetValue())));
	SaveTime->SetText(FText::FromString(FDateTime::FromUnixTimestamp(SaveGame->StartDate).ToFormattedString(TEXT("%Y-%m-%d %H:%M:%S"))));
	LastSave->SetText(FText::FromString(FDateTime::FromUnixTimestamp(SaveGame->LastPlayed).ToFormattedString(TEXT("%Y-%m-%d %H:%M:%S"))));
	SaveImage->SetBrushFromTexture(SaveGame->SaveImage);
}

USaveInformationSave* USaveSlotHUD::GetSaveSlot() const
{
	return SaveSlot;
}
