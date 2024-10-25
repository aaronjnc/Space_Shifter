// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"


class UImage;
/**
 * 
 */
UCLASS()
class SPACE_SHIFTER_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	UImage* PortalImage;
	
	UTextureRenderTarget2D* TextureRenderTarget;

	UPROPERTY(EditAnywhere, Category = "Rendering")
	TSubclassOf<AActor> SceneCaptureSubclass;

	UPROPERTY(EditAnywhere, Category = "Rendering")
	UMaterial* ParentMaterial;

	UMaterialInstanceDynamic* DynamicMaterial;

public:

	void GeneratePortalTexture();

	void DisplayCamera();
	
protected:

	
};
