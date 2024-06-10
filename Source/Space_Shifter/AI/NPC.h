// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Space_Shifter/Dialog/DialogComponent.h"
#include "Space_Shifter/Interactables/InteractableInterface.h"
#include "NPC.generated.h"

UCLASS()
class SPACE_SHIFTER_API ANPC : public ACharacter, public IInteractableInterface
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDialogComponent* DialogComponent;

public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	virtual void StopInteract() override;

};
