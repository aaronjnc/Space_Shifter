// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Portal.generated.h"

class AShifterController;
class APlayerCharacter;

UCLASS()
class SPACE_SHIFTER_API UPortal : public UStaticMeshComponent
{
	GENERATED_BODY()

private:

	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;

	AShifterController* ShifterController;

	UTextureRenderTarget2D* TextureRenderTarget;

	UPROPERTY(EditAnywhere, Category = "Rendering")
	TSubclassOf<AActor> SceneCaptureSubclass;

	UPROPERTY(EditAnywhere, Category = "Rendering")
	UMaterial* ParentMaterial;

	UMaterialInstanceDynamic* DynamicMaterial;

	TObjectPtr<AActor> SceneCaptureActor;

	UPROPERTY()
	USceneCaptureComponent2D* SceneCaptureComponent;

public:

	void UpdateCaptureLocation(FVector Location);

	void ActivatePortal();

	void DeactivatePortal();

	void GeneratePortalTexture();

	void UpdateCapture();

protected:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	void SetupCaptureSettings();
};
