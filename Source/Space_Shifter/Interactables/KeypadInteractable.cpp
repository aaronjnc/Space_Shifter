// Fill out your copyright notice in the Description page of Project Settings.


#include "KeypadInteractable.h"
#include "Components/BoxComponent.h"

AKeypadInteractable::AKeypadInteractable()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	CollisionComponent->SetupAttachment(RootComponent);
}
