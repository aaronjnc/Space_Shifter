// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Space_Shifter/PlayerCharacter.h"
#include "Interactable.generated.h"

class USphereComponent;
class AShifterController;

UCLASS()
class SPACE_SHIFTER_API AInteractable : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPrimitiveComponent* CollisionComponent;

	TWeakObjectPtr<AShifterController> PlayerController;
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact();

	virtual void StopInteract();

	UPrimitiveComponent* GetMesh();

};
