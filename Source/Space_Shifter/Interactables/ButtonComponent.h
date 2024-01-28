// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ButtonComponent.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API UButtonComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
private:

    UPROPERTY(EditAnywhere, Category = "Value")
	FString ButtonValue;

public:

	FString ButtonClick();
	
};
