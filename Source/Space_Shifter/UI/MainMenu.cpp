// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Space_Shifter/GameStructure/MenuGamemode.h"

void UMainMenu::Setup()
{
	AddToViewport();

	/*if (!ensure(StartGameButton != nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("Setup Start button"));
	StartGameButton->OnClicked.AddDynamic(this, &UMainMenu::Start);

	if (!ensure(SettingsButton != nullptr)) return;
	SettingsButton->OnClicked.AddDynamic(this, &UMainMenu::Setup);

	if (!ensure(QuitGameButton != nullptr)) return;
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);*/

	const UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputMode;
	//InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//PlayerController->SetInputMode(InputMode);
	
	PlayerController->SetShowMouseCursor(true);
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	StartGameButton->OnClicked.AddDynamic(this, &UMainMenu::Start);
	SettingsButton->OnClicked.AddDynamic(this, &UMainMenu::Setup);
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);

}

bool UMainMenu::Initialize()
{
	if (!Super::Initialize())
	{
		UE_LOG(LogTemp, Error, TEXT("Failure to initialize"));
		return false;
	}
	
	return true;
}

void UMainMenu::Start()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Clicked"));
	Cast<AMenuGamemode>(GetWorld()->GetAuthGameMode())->LoadGame();
}

void UMainMenu::SwitchScreen()
{
	ScreenSwitch->SetActiveWidgetIndex(1);
}

void UMainMenu::Quit()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	UKismetSystemLibrary::QuitGame(this, PlayerController,  EQuitPreference::Quit, true);
}
