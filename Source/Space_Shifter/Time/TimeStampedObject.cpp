// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeStampedObject.h"

#include "TimeManager.h"

void UTimeStampedObject::OnSaveTimeStamp(int TimeStamp)
{
	unimplemented();
}

void UTimeStampedObject::OnLoadTimeStamp(int TimeStamp)
{
	unimplemented();
}

void UTimeStampedObject::OnDeleteTimeStamp(int TimeStamp)
{
	unimplemented();
}

void UTimeStampedObject::SetupListeners()
{
	GetWorld()->GetSubsystem<UTimeManager>()->OnSaveTimeDelegate.AddDynamic(this, &UTimeStampedObject::OnSaveTimeStamp);
	GetWorld()->GetSubsystem<UTimeManager>()->OnLoadTimeDelegate.AddDynamic(this, &UTimeStampedObject::OnLoadTimeStamp);
	GetWorld()->GetSubsystem<UTimeManager>()->OnDeleteTimeDelegate.AddDynamic(this, &UTimeStampedObject::OnDeleteTimeStamp);
}
