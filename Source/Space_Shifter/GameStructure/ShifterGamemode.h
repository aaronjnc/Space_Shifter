 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShifterGamemode.generated.h"

/**
 * 
 */
enum EScene;
UCLASS()
class SPACE_SHIFTER_API AShifterGamemode : public AGameModeBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FName PlayerStartTag;

	UPROPERTY(EditAnywhere, Category = "Scenes")
	TMap<TEnumAsByte<EScene>, TSoftObjectPtr<UWorld>> SceneMapping;

protected:

	virtual void BeginPlay() override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

public:

	void ChangeScene(const TEnumAsByte<EScene> NewScene);
	
};
