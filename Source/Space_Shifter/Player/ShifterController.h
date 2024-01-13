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

	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
};
