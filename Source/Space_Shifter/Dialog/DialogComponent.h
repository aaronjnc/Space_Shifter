// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogComponent.generated.h"

struct FCharacterStruct
{
	FString CharacterName;
	FTexture* CharacterPortrait;
};

struct FDialogStruct
{
	FCharacterStruct* Character;
	FString Sentence;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACE_SHIFTER_API UDialogComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	FDialogStruct DialogStruct;

public:	
	// Sets default values for this component's properties
	UDialogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
