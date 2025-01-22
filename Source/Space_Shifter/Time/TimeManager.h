// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TimeManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSaveTimeDelegate, int, SaveNum);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadTimeDelegate, int, SaveNum);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleteTimeDelegate, int, SaveNum);

USTRUCT()
struct FTimeStamp
{
	GENERATED_BODY()

	FTimeStamp() : TimeStampId(0), TimeStamp(0) {}

	FTimeStamp(const int Id) : TimeStampId(Id), TimeStamp(0) {}

	UPROPERTY()
	int TimeStampId;
	
	UPROPERTY()
	float TimeStamp;
};

/**
 * 
 */
class ATimeEvent;

UCLASS()
class SPACE_SHIFTER_API UTimeManager : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FSaveTimeDelegate OnSaveTimeDelegate;

	UPROPERTY(BlueprintAssignable)
	FLoadTimeDelegate OnLoadTimeDelegate;

	UPROPERTY(BlueprintAssignable)
	FLoadTimeDelegate OnDeleteTimeDelegate;

private:

	const int MaxStamps = 5;
	
	float CountdownTimer;

	TDoubleLinkedList<ATimeEvent*> Events;

	TDoubleLinkedList<ATimeEvent*>::TDoubleLinkedListNode* NextTimeNode;

	float NextTriggerTime;

	bool bPastPaused = true;

	TMap<int, FTimeStamp*> UsedTimeStamps;

	TArray<FTimeStamp*> FreeTimeStamps;

public:

	bool HasAvailableTimeStamp();

	int DropTimeStamp();

	void LoadTimeStamp(const int &StampNumber);

	void DeleteTimeStamp(const int &StampNumber);

	void SetCountdownTimer(const float &TimeInMinutes);

	void AddEvent(ATimeEvent* TimeEvent);

	void PausePast();

	void LoadTime(const float &NewTime);

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	virtual void Tick(float DeltaTime) override;
	
};
