// Fill out your copyright notice in the Description page of Project Settings.


#include "ShifterGamemode.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void AShifterGamemode::BeginPlay()
{
	Super::BeginPlay();
}

AActor* AShifterGamemode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	for (AActor* PlayerStart : PlayerStarts)
	{
		if (PlayerStart->ActorHasTag(PlayerStartTag))
		{
			return PlayerStart;
		}
	}
	return Super::ChoosePlayerStart_Implementation(Player);
}

void AShifterGamemode::ChangeScene(const TEnumAsByte<EScene> NewScene)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, SceneMapping[NewScene]);
}
