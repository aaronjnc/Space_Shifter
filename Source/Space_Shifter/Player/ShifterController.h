// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShifterController.generated.h"


/**
 * 
 */
class UInputAction;
class UInputMappingContext;
class APlayerCharacter;
class UWidgetComponent;
class UDialogHUD;
UCLASS()
class SPACE_SHIFTER_API AShifterController : public APlayerController
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

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

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UDialogHUD> DialogHUDSubclass;
	
	UDialogHUD* DialogWidget;

	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;

public:

	FMatrix GetCameraProjectionMatrix();

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
};
