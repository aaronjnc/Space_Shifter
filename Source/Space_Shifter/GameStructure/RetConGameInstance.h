// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RetConGameInstance.generated.h"

/**
 * 
 */
class UMainMenu;
UCLASS()
class SPACE_SHIFTER_API URetConGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	UPROPERTY()
	UMainMenu* MainMenu;

	

public:

	void SetupMainMenu(TSubclassOf<UMainMenu> MainMenuClass);
	
};
