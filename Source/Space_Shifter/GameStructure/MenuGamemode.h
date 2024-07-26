// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGamemode.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API AMenuGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
};
