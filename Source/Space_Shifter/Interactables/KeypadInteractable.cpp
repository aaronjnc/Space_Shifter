// Fill out your copyright notice in the Description page of Project Settings.


#include "KeypadInteractable.h"
#include "Components/BoxComponent.h"
#include "Space_Shifter/Player/ShifterController.h"

AKeypadInteractable::AKeypadInteractable()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->SetSimulatePhysics(true);
}

void AKeypadInteractable::Interact()
{
	Super::Interact();
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetViewTargetWithBlend(this, 1.f);
}
