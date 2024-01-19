// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Space_Shifter/Player/ShifterController.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<AShifterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable::Interact()
{
	
}

UPrimitiveComponent* AInteractable::GetMesh()
{
	return CollisionComponent;
}
