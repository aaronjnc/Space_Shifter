// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeEvent.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SPACE_SHIFTER_API ATimeEvent : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Time")
	float TriggerTime = 0.0f;
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void BeginPlay() override;

	virtual void TriggerEvent();

	float GetTriggerTime();
};
