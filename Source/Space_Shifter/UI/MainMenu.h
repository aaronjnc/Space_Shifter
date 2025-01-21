// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
class UButton;
class UWidgetSwitcher;
UCLASS()
class SPACE_SHIFTER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:	

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* StartGameButton;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* SettingsButton;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UWidgetSwitcher* ScreenSwitch;

public:

	void SetupMenu();

protected:

	virtual void NativeConstruct() override;

	virtual bool Initialize() override;

private:

	UFUNCTION()
	void Start();

	UFUNCTION()
	void SwitchScreen();

	UFUNCTION()
	void Quit();
	
};
