// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSubsystem.h"
#include "EngineUtils.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void USaveGameSubsystem::WriteSave()
{
	CurrentSaveGame->SavedActorMap.Empty();

	AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		
	}
}

void USaveGameSubsystem::LoadSave()
{
	
}
