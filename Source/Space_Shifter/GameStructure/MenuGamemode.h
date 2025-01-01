// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Space_Shifter/UI/MainMenu.h"
#include "MenuGamemode.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API AMenuGamemode : public AGameModeBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UMainMenu> MainMenuClass;

public:

	virtual void BeginPlay() override;

	void LoadGame();
	
};
