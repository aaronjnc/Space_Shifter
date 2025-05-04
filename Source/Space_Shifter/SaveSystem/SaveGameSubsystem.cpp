// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSubsystem.h"
#include "EngineUtils.h"
#include "SavedObject.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Space_Shifter/PlayerCharacter.h"
#include "Space_Shifter/Player/ShifterController.h"

void USaveGameSubsystem::CreateNewSave(const FString& SaveName)
{
	const FString GameSavePath = GetSavePath(SaveName, GGameSaveLocation);
	const FString PlayerPath = GetSavePath(SaveName, GPlayerSave);
	const FString LevelSavePath = GetSavePath(SaveName, GLevelSave);
	TArray<FString> TimeSlots;
	for (int i = 0; i < 5; i++)
	{
		TimeSlots.Add(FString::Printf(TEXT("%s_%d"), *GetSavePath(SaveName, GTimeSlotSave), i+1));
	}
	
	if (!UGameplayStatics::DoesSaveGameExist(GameSavePath, 0))
	{
		UUserSaveGame* UserSave = Cast<UUserSaveGame>(UGameplayStatics::CreateSaveGameObject(UUserSaveGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(UserSave, GameSavePath, 0);
		URetConPlayerSave* PlayerSave = Cast<URetConPlayerSave>(UGameplayStatics::CreateSaveGameObject(URetConPlayerSave::StaticClass()));
		UGameplayStatics::SaveGameToSlot(PlayerSave, PlayerPath, 0);
		URetConEnvironmentSave* LevelSave = Cast<URetConEnvironmentSave>(UGameplayStatics::CreateSaveGameObject(URetConEnvironmentSave::StaticClass()));
		UGameplayStatics::SaveGameToSlot(LevelSave, LevelSavePath, 0);
		for (FString TimeSlot : TimeSlots)
		{
			URetConEnvironmentSave* TimeSlotSave = Cast<URetConEnvironmentSave>(UGameplayStatics::CreateSaveGameObject(URetConEnvironmentSave::StaticClass()));
			UGameplayStatics::SaveGameToSlot(TimeSlotSave, TimeSlot, 0);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Save Game with name %s already exists."), SaveName);
	}
}

void USaveGameSubsystem::DeleteSave(const FString& SaveName) 
{
	TArray<FString> SavePaths;
	SavePaths.Add(GetSavePath(SaveName, GGameSaveLocation));
	SavePaths.Add(GetSavePath(SaveName, GPlayerSave));
	SavePaths.Add(GetSavePath(SaveName, GLevelSave));
	for (int i = 0; i < 5; i++)
	{
		SavePaths.Add(FString::Printf(TEXT("%s_%d"), *GetSavePath(SaveName, GTimeSlotSave), i+1));
	}
	for (FString Path : SavePaths)
	{
		if (UGameplayStatics::DoesSaveGameExist(Path, 0))
		{
			UGameplayStatics::DeleteGameInSlot(Path, 0);
		}
	}
}

TArray<FString> USaveGameSubsystem::GetSaves()
{
	TArray<FString> SaveNames;

	if (!UGameplayStatics::DoesSaveGameExist(GSystemSave, 0))
	{
		
		return SaveNames;
	}
	const FString& SaveFolder = FPaths::ProjectSavedDir();
	
	IFileManager& FileManager = IFileManager::Get();

	TArray<FString> FileNames;
	FileManager.FindFiles(FileNames, *SaveFolder, true, false);
	for (FString File : FileNames)
	{
		FString GameName, SaveType;
		File.Split(",", &GameName, &SaveType);
		if (SaveType.Equals(GGameSaveLocation))
		{
			SaveNames.Add(GameName);
		}
	}
	return SaveNames;
}

void USaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//const UGameUserSettings* Settings = GetDefault<UGameUserSettings>();
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

	const FString EnvSaveSlot = GetSavePath(CurrentSaveSlot, SaveName);
	if (!UGameplayStatics::SaveGameToSlot(CurrentEnvironmentSave, EnvSaveSlot, 0))
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to save environment to %s"), EnvSaveSlot);
	}
}

void USaveGameSubsystem::SavePlayer()
{
	AShifterController* Controller = CastChecked<AShifterController>(UGameplayStatics::GetPlayerCharacter(this, 0));
	Controller->SavePlayerInfo(CurrentPlayerSave);

	const FString PlayerSaveSlot = CurrentSaveSlot + PlayerSaveSlot;
	if (!UGameplayStatics::SaveGameToSlot(CurrentPlayerSave, PlayerSaveSlot, 0))
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to save player to %s"), PlayerSaveSlot);
	}
}

void USaveGameSubsystem::LoadSave(const FString& SaveName)
{
	const FString PlayerSaveSlot = CurrentSaveSlot + PlayerSaveSlot;
	if (UGameplayStatics::DoesSaveGameExist(PlayerSaveSlot, 0))
	{
		CurrentPlayerSave = Cast<URetConPlayerSave>(UGameplayStatics::LoadGameFromSlot(PlayerSaveSlot, 0));
		if (!CurrentPlayerSave)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load Player data"));
			return;
		}

		AShifterController* Controller = CastChecked<AShifterController>(UGameplayStatics::GetPlayerCharacter(this, 0));

		FMemoryReader MemReader(CurrentPlayerSave->PlayerSave.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
		Ar.ArIsSaveGame = true;

		Controller->Serialize(Ar);

		Controller->LoadPlayerInfo(CurrentPlayerSave);
	}
	LoadEnvironment(SaveName);
}

void USaveGameSubsystem::LoadEnvironment(const FString& SaveName)
{
	const FString EnvSave = CurrentSaveSlot + "_" + SaveName;
	if (UGameplayStatics::DoesSaveGameExist(EnvSave, 0))
	{
		CurrentEnvironmentSave = Cast<URetConEnvironmentSave>(UGameplayStatics::LoadGameFromSlot(EnvSave, 0));
		if (!CurrentEnvironmentSave)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load SaveGame data"));
			return;
		}

		for (AActor* Actor : TActorRange<AActor>(GetWorld()))
		{
			if (!IsValid(Actor) || !Actor->Implements<USavedObject>())
			{
				continue;
			}

			if (CurrentEnvironmentSave->SavedActorMap.Contains(Actor->GetFName()))
			{
				FActorSaveData ActorData = CurrentEnvironmentSave->SavedActorMap[Actor->GetFName()];
				Actor->SetActorTransform(ActorData.Transform);

				FMemoryReader MemReader(ActorData.ByteData);

				FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
				Ar.ArIsSaveGame = true;

				Actor->Serialize(Ar);
			}
		}
	}
}

FString USaveGameSubsystem::GetSavePath(const FString& SaveName, const FString& SaveType)
{
	return FString::Printf(TEXT("%s_%s"), *SaveName, *SaveType);
}
