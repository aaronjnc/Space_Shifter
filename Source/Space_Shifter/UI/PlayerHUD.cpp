// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Space_Shifter/PlayerCharacter.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UPlayerHUD::GeneratePortalTexture()
{
	int32 CurrentSizeX = 1920;
    int32 CurrentSizeY = 1080;

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

void UPlayerHUD::DisplayCamera()
{
    
}
