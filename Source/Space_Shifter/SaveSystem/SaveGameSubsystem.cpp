// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSubsystem.h"
#include "EngineUtils.h"
#include "SavedObject.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Space_Shifter/Player/ShifterController.h"

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
	CurrentEnvironmentSave->SavedActorMap.Empty();

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

		CurrentEnvironmentSave->SavedActorMap.Add(Actor->GetFName(), ActorData);
	}

	const FString EnvSaveSlot = CurrentSaveSlot + SaveName;
	UGameplayStatics::SaveGameToSlot(CurrentEnvironmentSave, EnvSaveSlot, 0);
}

void USaveGameSubsystem::SavePlayer()
{
	AShifterController* Controller = CastChecked<AShifterController>(UGameplayStatics::GetPlayerCharacter(this, 0));
	Controller->SavePlayerInfo(CurrentPlayerSave);

	const FString PlayerSaveSlot = CurrentSaveSlot + PlayerSaveSlot;
	UGameplayStatics::SaveGameToSlot(CurrentPlayerSave, PlayerSaveSlot, 0);
}

void USaveGameSubsystem::LoadSave()
{
	
}
