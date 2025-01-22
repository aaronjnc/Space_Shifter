// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeEvent.h"

#include "TimeManager.h"

// Add default functionality here for any ITimeEvent functions that are not pure virtual.
void ATimeEvent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetSubsystem<UTimeManager>()->AddEvent(this);
}

void ATimeEvent::TriggerEvent()
{
	unimplemented();
}

float ATimeEvent::GetTriggerTime()
{
	return TriggerTime;
}
