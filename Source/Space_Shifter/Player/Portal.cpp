// Fill out your copyright notice in the Description page of Project Settings.

#include "Portal.h"
#include "GameFramework/Actor.h"
#include "Space_Shifter/PlayerCharacter.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "ShifterController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UPortal::UpdateCaptureLocation(FVector Location)
{
	SceneCaptureActor->SetActorLocation(Location);
	SceneCaptureActor->SetActorRotation(PlayerCharacter->GetActorRotation());
	SceneCaptureComponent->CaptureScene();
}

void UPortal::ActivatePortal()
{
	SetVisibility(true);
}

void UPortal::DeactivatePortal()
{
	SetVisibility(false);
}

void UPortal::GeneratePortalTexture()
{
	int32 CurrentSizeX = 1920;
    int32 CurrentSizeY = 1080;

    if( ShifterController != nullptr )
    {
        ShifterController->GetViewportSize(CurrentSizeX, CurrentSizeY);
    }

    // Use a smaller size than the current 
    // screen to reduce the performance impact
    CurrentSizeX = FMath::Clamp( int(CurrentSizeX / 1.7), 128, 1920); //1920 / 1.5 = 1280
    CurrentSizeY = FMath::Clamp( int(CurrentSizeY / 1.7), 128, 1080);
	
    // Create the RenderTarget if it does not exist
    if( TextureRenderTarget == nullptr )
    {
        // Create new RTT
        TextureRenderTarget = NewObject<UTextureRenderTarget2D>(
            this,
            UTextureRenderTarget2D::StaticClass(),
            *FString("PortalRenderTarget")
        );
        check( TextureRenderTarget );

        TextureRenderTarget->RenderTargetFormat   = ETextureRenderTargetFormat::RTF_RGBA16f;
        TextureRenderTarget->Filter               = TextureFilter::TF_Bilinear;
        TextureRenderTarget->SizeX                = CurrentSizeX;
        TextureRenderTarget->SizeY                = CurrentSizeY;
        TextureRenderTarget->ClearColor           = FLinearColor::Black;
        TextureRenderTarget->TargetGamma          = 2.2f;
        TextureRenderTarget->bNeedsTwoCopies      = false;
        TextureRenderTarget->AddressX             = TextureAddress::TA_Clamp;
        TextureRenderTarget->AddressY             = TextureAddress::TA_Clamp;

        // Not needed since the texture is displayed on screen directly
        // in some engine versions this can even lead to crashes (notably 4.24/4.25)
        TextureRenderTarget->bAutoGenerateMips    = false;

        // This force the engine to create the render target 
        // with the parameters we defined just above
        TextureRenderTarget->UpdateResource();
    }
    // Resize the RenderTarget if it already exists
    else
    {
        TextureRenderTarget-> ResizeTarget( CurrentSizeX, CurrentSizeY );
    }
}

void UPortal::UpdateCapture()
{
	if( ShifterController == nullptr )
    {
        return;
    }

    //-----------------------------------
    // Update SceneCapture (discard if there is no active portal)
    //-----------------------------------
    if(SceneCaptureComponent     != nullptr
    && TextureRenderTarget    != nullptr
    && PlayerCharacter        != nullptr )
    {

        UCameraComponent* PlayerCamera = PlayerCharacter->GetCameraComponent();

        //-------------------------------
        //Clip Plane : to ignore objects between the
        //SceneCapture and the Target of the portal
        //-------------------------------
        SceneCaptureComponent->ClipPlaneNormal   = -UKismetMathLibrary::GetForwardVector(GetComponentRotation());
        SceneCaptureComponent->ClipPlaneBase     = SceneCaptureActor->GetActorLocation() +
        	GetRelativeLocation() + (SceneCaptureComponent->ClipPlaneNormal * -1.5f); //Offset to avoid visible pixel border
    	
        // Assign the Render Target
    	DynamicMaterial->SetTextureParameterValue(TEXT("txt_Portal"), TextureRenderTarget);
        SceneCaptureComponent->TextureTarget = TextureRenderTarget;

        SceneCaptureComponent->CaptureScene();
    }
}

void UPortal::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	const FActorSpawnParameters SpawnParameters;
	SceneCaptureActor = GetWorld()->SpawnActor<AActor>(SceneCaptureSubclass, PlayerCharacter->GetActorLocation(), PlayerCharacter->GetActorRotation(), SpawnParameters);
	SceneCaptureComponent = SceneCaptureActor->GetComponentByClass<USceneCaptureComponent2D>();
	SceneCaptureComponent->TextureTarget = TextureRenderTarget;

	ShifterController = Cast<AShifterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	DynamicMaterial = CreateDynamicMaterialInstance(0, ParentMaterial);
	SetMaterial(0, DynamicMaterial);

	GeneratePortalTexture();

	UpdateCapture();

	DeactivatePortal();
}

void UPortal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsVisible())
	{
		UpdateCapture();
	}
}

void UPortal::SetupCaptureSettings()
{
	FPostProcessSettings CaptureSettings;

	CaptureSettings.bOverride_AmbientOcclusionQuality       = true;
	CaptureSettings.bOverride_MotionBlurAmount              = true;
	CaptureSettings.bOverride_SceneFringeIntensity          = true;
	CaptureSettings.bOverride_FilmGrainIntensity                = true;
	CaptureSettings.bOverride_ScreenSpaceReflectionQuality  = true;

	CaptureSettings.AmbientOcclusionQuality         = 0.0f; //0=lowest quality..100=maximum quality
	CaptureSettings.MotionBlurAmount                = 0.0f; //0 = disabled
	CaptureSettings.SceneFringeIntensity            = 0.0f; //0 = disabled
	CaptureSettings.FilmGrainIntensity                  = 0.0f; //0 = disabled
	CaptureSettings.ScreenSpaceReflectionQuality    = 0.0f; //0 = disabled

	SceneCaptureComponent->PostProcessSettings = CaptureSettings;
}
