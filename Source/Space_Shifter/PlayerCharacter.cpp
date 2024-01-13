// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Player/Portal.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(RootComponent);

	PortalComponent = CreateDefaultSubobject<UPortal>("Portal Component");
	PortalComponent->SetupAttachment(RootComponent);

	bInTheFuture = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	for (const AActor* PlayerStart : PlayerStarts)
	{
		if (PlayerStart->ActorHasTag(FutureStartTag))
		{
			FutureStartPosition = PlayerStart->GetActorLocation();
		}
		else if (PlayerStart->ActorHasTag(PastStartTag))
		{
			PastStartPosition = PlayerStart->GetActorLocation();
		}
	}
	if (bInTheFuture)
	{
		PortalComponent->UpdateCaptureLocation(GetActorLocation() - FutureStartPosition + PastStartPosition);
	}
	else
	{
		PortalComponent->UpdateCaptureLocation(GetActorLocation() - PastStartPosition + FutureStartPosition);
	}
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

void APlayerCharacter::ShiftTime()
{
	FVector RefPosition = PastStartPosition;
	FVector NewRefPosition = FutureStartPosition;
	if (bInTheFuture)
	{
		RefPosition = FutureStartPosition;
		NewRefPosition = PastStartPosition;
	}
	const FVector RelativePosition = GetActorLocation() - RefPosition + NewRefPosition;
	SetActorLocation(RelativePosition);
	bInTheFuture = !bInTheFuture;
	PortalComponent->UpdateCaptureLocation(GetActorLocation() - NewRefPosition + RefPosition);
}

void APlayerCharacter::ActivatePortal()
{
	
}

void APlayerCharacter::DeactivatePortal()
{
	
}
