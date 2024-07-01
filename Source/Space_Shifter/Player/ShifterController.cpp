// Fill out your copyright notice in the Description page of Project Settings.


#include "ShifterController.h"
#include "InputAction.h"
#include "Space_Shifter/PlayerCharacter.h"
#include "Space_Shifter/Dialog/DialogHUD.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "StereoRendering.h"
#include "SceneView.h"
#include "Kismet/KismetMathLibrary.h"
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

void AShifterController::SetMappingContext(const EMappingContexts& NewContext)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(MappingContexts[NewContext], 0);
		UE_LOG(LogTemp, Warning, TEXT("Mapping context switched %s"), *UEnum::GetValueAsString(NewContext));
	}
}

void AShifterController::SetupInput()
{
	SetupInputComponent();
}

void AShifterController::BeginPlay()
{
	Super::BeginPlay();

	SetMappingContext(EMappingContexts::DefaultContext);

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
	if (!PlayerCharacter.IsValid() || bInputSetup )
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
		EnhancedInputComponent->BindAction(TalkAction, ETriggerEvent::Completed, this, &AShifterController::ContinueDialog);
	}
	bInputSetup = true;
}

void AShifterController::ContinueDialog()
{
	if (!DialogWidget->NextLine()) {
	    DialogWidget->SetVisibility(ESlateVisibility::Hidden);
		SetMappingContext(EMappingContexts::DefaultContext);
	}
}
