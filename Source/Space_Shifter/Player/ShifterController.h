// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Space_Shifter/SaveSystem/RetConSaveGame.h"
#include "ShifterController.generated.h"

/**
 * 
 */
class UInputAction;
class UInputMappingContext;
class APlayerCharacter;
class UWidgetComponent;
class UDialogHUD;

UENUM(BlueprintType)
enum EMappingContexts
{
	DefaultContext,
	Empty,
	Dialog,
	MouseInteraction,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSavePlayerDelegate, URetConPlayerSave*, PlayerSave);

UCLASS()
class SPACE_SHIFTER_API AShifterController : public APlayerController
{
	GENERATED_BODY()

public:

	FSavePlayerDelegate OnPlayerSaved;

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	TMap<TEnumAsByte<EMappingContexts>, UInputMappingContext*> MappingContexts;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ShiftAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* PortalAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TalkAction;
	
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UDialogHUD> DialogHUDSubclass;
	
	UDialogHUD* DialogWidget;

	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;

	bool bInputSetup = false;

public:

	FMatrix GetCameraProjectionMatrix();

	void SetMappingContext(const EMappingContexts& NewContext);

	void SetupInput();

	void SavePlayerInfo(URetConPlayerSave* PlayerSave);

	void LoadPlayerInfo(URetConPlayerSave* PlayerSave);

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void ContinueDialog();
	
};
