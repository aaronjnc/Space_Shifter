// Fill out your copyright notice in the Description page of Project Settings.


#include "RetConGameInstance.h"
#include "Space_Shifter/UI/MainMenu.h"
#include "Blueprint/UserWidget.h"

void URetConGameInstance::SetupMainMenu(TSubclassOf<UMainMenu> MainMenuClass)
{
	MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);

	if (!ensure(MainMenu != nullptr)) return;

	if (IsValid(MainMenu))
	{
		UE_LOG(LogTemp, Warning, TEXT("Valid"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid"));
	}
	
	MainMenu->Setup();
}
