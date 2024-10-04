// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CutscenePawn.generated.h"

class UImagePlateComponent;
class UCineCameraComponent;
UCLASS()
class SPACE_SHIFTER_API ACutscenePawn : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UImagePlateComponent* ImagePlate;

	UPROPERTY(VisibleAnywhere, Category = "Compoents")
	UCineCameraComponent* CineCamera;

public:
	// Sets default values for this pawn's properties
	ACutscenePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
