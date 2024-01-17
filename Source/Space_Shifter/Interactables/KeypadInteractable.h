// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "KeypadInteractable.generated.h"


class UBoxComponent;
/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API AKeypadInteractable : public AInteractable
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Buttons")
	FVector2D ButtonDimensions;

	TArray<UBoxComponent*> ButtonBoxes;

public:

	AKeypadInteractable();
	
};
