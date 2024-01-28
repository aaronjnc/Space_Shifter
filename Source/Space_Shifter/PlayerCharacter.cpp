// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Interactables/Interactable.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Player/Grabber.h"
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

	GrabberComponent = CreateDefaultSubobject<UGrabber>("Grabber Component");
	GrabberComponent->SetupAttachment(CameraComponent);

	PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>("Physics Handle");
	
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
	UpdateCaptureLocation();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsInteracting)
	{
		return;
	}

	FHitResult HitResult;
	const FVector& CameraLoc = GetCameraComponent()->GetComponentLocation();
	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraLoc, CameraLoc + CameraComponent->GetForwardVector() * InteractDistance, ECC_GameTraceChannel2))
	{
		if (HitResult.GetActor()->IsA(AInteractable::StaticClass()))
		{
			InteractObject = Cast<AInteractable>(HitResult.GetActor());	
		}
		else
		{
			InteractObject = nullptr;
		}
	}
	else
	{
		InteractObject = nullptr;
	}
	if (bPortalActive)
	{
		UpdateCaptureLocation();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (bIsInteracting)
	{
		return;
	}
	const FVector2D MoveDir = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MoveDir.Y);
	AddMovementInput(GetActorRightVector(), MoveDir.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if (bIsInteracting)
	{
		return;
	}
	const FVector2D LookDir = Value.Get<FVector2D>();

	AddControllerYawInput(LookDir.X);
	AddControllerPitchInput(LookDir.Y);
}

void APlayerCharacter::Interact()
{
	if (GrabberComponent->GetIsGrabbing())
	{
		GrabberComponent->Release();
	}
	if (!InteractObject.IsValid())
	{
		return;
	}
	if (InteractObject->Tags.Contains("Grabbable"))
	{
		GrabberComponent->Grab(InteractObject.Get());
	}
	else if (!bIsInteracting)
	{
		bIsInteracting = true;
		InteractObject->Interact();
	}
	else
	{
		InteractObject->StopInteract();
		bIsInteracting = false;
	}
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
	UpdateCaptureLocation();
}

void APlayerCharacter::PortalAction()
{
	if (bPortalActive)
	{
		DeactivatePortal();
	}
	else
	{
		ActivatePortal();
	}
	bPortalActive = !bPortalActive;
}

UCameraComponent* APlayerCharacter::GetCameraComponent()
{
	return CameraComponent;
}

void APlayerCharacter::ActivatePortal()
{
	PortalComponent->ActivatePortal();
}

void APlayerCharacter::DeactivatePortal()
{
	PortalComponent->DeactivatePortal();
}

void APlayerCharacter::UpdateCaptureLocation()
{
	if (bInTheFuture)
	{
		PortalComponent->UpdateCaptureLocation(PortalComponent->GetComponentLocation() - FutureStartPosition + PastStartPosition);
	}
	else
	{
		PortalComponent->UpdateCaptureLocation(PortalComponent->GetComponentLocation() - PastStartPosition + FutureStartPosition);
	}
}
