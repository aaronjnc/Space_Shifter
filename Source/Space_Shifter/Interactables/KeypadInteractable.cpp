// Fill out your copyright notice in the Description page of Project Settings.


#include "KeypadInteractable.h"

#include "ButtonComponent.h"
#include "Components/BoxComponent.h"
#include "Space_Shifter/Player/ShifterController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

AKeypadInteractable::AKeypadInteractable()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->SetSimulatePhysics(true);
}

EMappingContexts AKeypadInteractable::Interact()
{
	Super::Interact();
	PlayerController->SetShowMouseCursor(true);
	//PlayerController->SetViewTargetWithBlend(this, 0.1f);
	UCameraComponent* CameraComponent = PlayerCharacter->GetCameraComponent();
	CameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	CameraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CameraComponent->SetRelativeLocation(CameraLocation);
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetRelativeRotation(FRotator::ZeroRotator);
	UE_LOG(LogTemp, Warning, TEXT("New Rotation: %s"), *CameraComponent->GetRelativeRotation().ToString());
	
	return EMappingContexts::MouseInteraction;
}

EMappingContexts AKeypadInteractable::StopInteract()
{
	Super::StopInteract();
	PlayerController->bShowMouseCursor = false;
	UCameraComponent* CameraComponent = PlayerCharacter->GetCameraComponent();
	CameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	CameraComponent->AttachToComponent(PlayerCharacter->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CameraComponent->SetRelativeLocation(FVector(0, 0, 50));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetRelativeRotation(FRotator::ZeroRotator);

	return EMappingContexts::DefaultContext;
}

void AKeypadInteractable::Click()
{
	FVector StartPosition;
	FVector Dir;

	PlayerController->DeprojectMousePositionToWorld(StartPosition, Dir);

	DrawDebugLine(GetWorld(), StartPosition, StartPosition + Dir * 1000, FColor::Red);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartPosition, StartPosition + Dir * 1000, ECC_Visibility))
	{
		if (Hit.GetComponent()->IsA<UButtonComponent>())
		{
			UButtonComponent* ButtonHit = Cast<UButtonComponent>(Hit.GetComponent());
			const FString& ButtonString = ButtonHit->ButtonClick();
			UE_LOG(LogTemp, Warning, TEXT("Button String: %s"), *ButtonString);
		}
	}
}

void AKeypadInteractable::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(BeginPlayHandle, this, &AKeypadInteractable::BeginPlayDelayed, .1f, false);
}

void AKeypadInteractable::BeginPlayDelayed()
{
	if (PlayerController.IsValid())
	{
		PlayerController->SetupInput();
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Completed, this, &AKeypadInteractable::Click);
			BindingNum = EnhancedInputComponent->GetNumActionBindings() - 1;
		}
	}
}
