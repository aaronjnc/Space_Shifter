// Fill out your copyright notice in the Description page of Project Settings.


#include "ShifterController.h"
#include "InputAction.h"
#include "Space_Shifter/PlayerCharacter.h"
#include "Space_Shifter/Dialog/DialogHUD.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "StereoRendering.h"
#include "SceneView.h"
#include "Space_Shifter/Dialog/DialogManager.h"

FMatrix AShifterController::GetCameraProjectionMatrix()
{
	FMatrix ProjectionMatrix;

	if( GetLocalPlayer() != nullptr )
	{
		FSceneViewProjectionData PlayerProjectionData;

		GetLocalPlayer()->GetProjectionData( GetLocalPlayer()->ViewportClient->Viewport, PlayerProjectionData);
		
		ProjectionMatrix = PlayerProjectionData.ProjectionMatrix;
	}

	return ProjectionMatrix;
}

void AShifterController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (IsValid(DialogHUDSubclass))
	{
		DialogWidget = CreateWidget<UDialogHUD>(this, DialogHUDSubclass);
		DialogWidget->AddToViewport();
		DialogWidget->SetVisibility(ESlateVisibility::Hidden);

		GetGameInstance()->GetSubsystem<UDialogManager>()->AssignDialogHUD(DialogWidget);
	}

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	
	SetupInputComponent();
	SetShowMouseCursor(false);
}

void AShifterController::SetupInputComponent()
{
	if (!PlayerCharacter.IsValid())
	{
		return;
	}
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, PlayerCharacter.Get(), &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, PlayerCharacter.Get(), &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, PlayerCharacter.Get(), &APlayerCharacter::ShiftTime);
		EnhancedInputComponent->BindAction(PortalAction, ETriggerEvent::Completed, PlayerCharacter.Get(), &APlayerCharacter::PortalAction);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, PlayerCharacter.Get(), &APlayerCharacter::Interact);
	}
}
