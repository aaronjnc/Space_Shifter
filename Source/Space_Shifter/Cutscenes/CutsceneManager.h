// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "Space_Shifter/GameStructure/QuestManager.h"
#include "CutsceneManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACE_SHIFTER_API UCutsceneManager : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
	ULevelSequencePlayer* SequencePlayer;

	UPROPERTY()
	ULevelSequence* LevelSequence;

public:	
	// Sets default values for this component's properties
	UCutsceneManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
