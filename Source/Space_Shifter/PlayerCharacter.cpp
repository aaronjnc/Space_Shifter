// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveDir = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MoveDir.Y);
	AddMovementInput(GetActorRightVector(), MoveDir.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookDir = Value.Get<FVector2D>();

	AddControllerYawInput(LookDir.X);
	AddControllerPitchInput(LookDir.Y);
}

