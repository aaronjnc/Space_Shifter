// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameHUD.h"
#include "SaveSlotHUD.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Space_Shifter/SaveSystem/SaveGameSubsystem.h"
#include "Components/Image.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void USaveGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	WorldRef = GetWorld();

	if (WorldRef)
    {
        // Safe to use World here
        UE_LOG(LogTemp, Log, TEXT("World is: %s"), *WorldRef->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("World was null in NativeConstruct"));
    }

	UpdateSaveList();

	UE_LOG(LogTemp, Warning, TEXT("Create Bindings"));
	SaveList->OnItemSelectionChanged().AddUObject(this, &USaveGameHUD::SelectSave);
	CreateSave->OnClicked.AddDynamic(this, &USaveGameHUD::CreateGame);
}

void USaveGameHUD::SelectSave(UObject* Item)
{
	USaveInformationSave* SaveGame = Cast<USaveSlotHUD>(Item)->GetSaveSlot();
	SaveName->SetText(FText::FromString(SaveGame->SaveName));
	CurrentLevel->SetText(FText::FromString(UEnum::GetValueAsString(SaveGame->CurrentLevel.GetValue())));
	FirstSave->SetText(FText::FromString(FDateTime::FromUnixTimestamp(SaveGame->StartDate).ToFormattedString(TEXT("%Y-%m-%d %H:%M:%S"))));
	LastSave->SetText(FText::FromString(FDateTime::FromUnixTimestamp(SaveGame->LastPlayed).ToFormattedString(TEXT("%Y-%m-%d %H:%M:%S"))));
	SaveImage->SetBrushFromTexture(SaveGame->SaveImage);
	Difficulty->SetText(FText::FromString(UEnum::GetValueAsString(SaveGame->Difficulty)));
}

void USaveGameHUD::CreateGame()
{
	USaveInformationSave* SaveInfo = Cast<USaveInformationSave>(UGameplayStatics::CreateSaveGameObject(USaveInformationSave::StaticClass()));
	SaveInfo->SaveName = NewSaveName->GetText().ToString();
	USaveGameSubsystem::CreateNewSave(SaveInfo);
	UpdateSaveList();
}

void USaveGameHUD::UpdateSaveList()
{
	UE_LOG(LogTemp, Warning, TEXT("Update Save List"));
	SaveList->ClearListItems();

	TArray<USaveInformationSave*> GameSaves = USaveGameSubsystem::GetSaves();

	if (GameSaves.Num() == 0)
	{
		return;
	}

	for (USaveInformationSave* GameSave : GameSaves)
	{
		USaveSlotHUD* NewItem = CreateWidget<USaveSlotHUD>(WorldRef, USaveSlotHUD::StaticClass());
		NewItem->SetupSaveSlot(GameSave);
		SaveList->AddItem(NewItem);
	}

}
