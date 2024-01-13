 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShifterGamemode.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API AShifterGamemode : public AGameModeBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FName PlayerStartTag;

protected:

	virtual void BeginPlay() override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
};
