// Fill out your copyright notice in the Description page of Project Settings.


#include "CutsceneManager.h"
#include "Space_Shifter/GameStructure/QuestManager.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequenceActor.h"

// Sets default values for this component's properties
UCutsceneManager::UCutsceneManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCutsceneManager::BeginPlay()
{
	Super::BeginPlay();

	ALevelSequenceActor* LevelSequenceActor;
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	LevelSequence = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UQuestManager>()->GetCutscene();
	SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, PlaybackSettings, LevelSequenceActor);
	SequencePlayer->PlayLooping();
}


// Called every frame
void UCutsceneManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

