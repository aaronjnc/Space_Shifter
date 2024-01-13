// Fill out your copyright notice in the Description page of Project Settings.

#include "Portal.h"
#include "GameFramework/Actor.h"
#include "Space_Shifter/PlayerCharacter.h"
#include "Components/SceneCaptureComponent2D.h"

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

void UPortal::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	const FActorSpawnParameters SpawnParameters;
	SceneCaptureActor = GetWorld()->SpawnActor<AActor>(SceneCaptureSubclass, PlayerCharacter->GetActorLocation(), PlayerCharacter->GetActorRotation(), SpawnParameters);
	SceneCaptureComponent = SceneCaptureActor->GetComponentByClass<USceneCaptureComponent2D>();
	SceneCaptureComponent->TextureTarget = TextureRenderTarget;
}

void UPortal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SceneCaptureComponent->CaptureScene();
}
