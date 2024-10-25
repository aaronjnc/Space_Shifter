// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGamemode.h"

#include "QuestManager.h"
#include "RetConGameInstance.h"

void AMenuGamemode::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(MainMenuClass != nullptr)) return;

	GetGameInstance<URetConGameInstance>()->SetupMainMenu(MainMenuClass);

	/*UMainMenu* MainMenu = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);

	if (!ensure(MainMenu != nullptr)) return;

	if (IsValid(MainMenu))
	{
		UE_LOG(LogTemp, Warning, TEXT("Valid"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid"));
		
	}

	MainMenu->AddToViewport();
	
	MainMenu->Setup();*/
}

void AMenuGamemode::LoadGame()
{
	GetGameInstance()->GetSubsystem<UQuestManager>()->LoadQuest(0);
}
