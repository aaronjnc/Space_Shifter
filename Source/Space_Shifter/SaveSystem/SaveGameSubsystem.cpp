// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSubsystem.h"
#include "EngineUtils.h"
#include "SavedObject.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void USaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UGameUserSettings* Settings = GetDefault<UGameUserSettings>();
}

void USaveGameSubsystem::SaveGame()
{
	SaveEnvironment(GGameSaveLocation);
	SavePlayer();
}

void USaveGameSubsystem::SaveEnvironment(const FString& SaveName)
{
	CurrentSaveGame->SavedActorMap.Empty();

	AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	for (AActor* Actor : TActorRange<AActor>(GetWorld()))
	{
		if (!IsValid(Actor) || !Actor->Implements<USavedObject>())
		{
			continue;
		}
		
		FActorSaveData ActorData;
		ActorData.ActorName = Actor->GetName();
		ActorData.Transform = Actor->GetActorTransform();

		FMemoryWriter MemWriter(ActorData.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);

		Ar.ArIsSaveGame = true;

		Actor->Serialize(Ar);

		CurrentSaveGame->SavedActorMap.Add(Actor->GetFName(), ActorData);
	}

	FString EnvSaveSlot = CurrentSaveSlot + SaveName;
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, EnvSaveSlot, 0);
}

void USaveGameSubsystem::SavePlayer()
{
	
}

void USaveGameSubsystem::LoadSave()
{
	
}
