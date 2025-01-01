// Fill out your copyright notice in the Description page of Project Settings.


#include "CutscenePawn.h"
#include "CineCameraComponent.h"
#include "ImagePlateComponent.h"

// Sets default values
ACutscenePawn::ACutscenePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CineCamera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("Cine Camera"));
	CineCamera->SetupAttachment(RootComponent);

	ImagePlate = CreateDefaultSubobject<UImagePlateComponent>(TEXT("Image Plate"));
	ImagePlate->SetupAttachment(CineCamera);
}

// Called when the game starts or when spawned
void ACutscenePawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACutscenePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACutscenePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

