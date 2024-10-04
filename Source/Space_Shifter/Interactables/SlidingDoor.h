// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Space_Shifter/Dialog/DialogActionInterface.h"
#include "SlidingDoor.generated.h"

UCLASS()
class SPACE_SHIFTER_API ASlidingDoor : public AActor, public IDialogActionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlidingDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PerformDialogAction() override;

};
