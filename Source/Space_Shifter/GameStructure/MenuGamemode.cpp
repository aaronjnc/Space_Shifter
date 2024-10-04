// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGamemode.h"

#include "QuestManager.h"

void AMenuGamemode::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<UQuestManager>()->LoadQuest(0);
}
