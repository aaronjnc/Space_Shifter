// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"

#include "TimeEvent.h"
#include "Kismet/GameplayStatics.h"
#include "Space_Shifter/GameStructure/QuestManager.h"

bool UTimeManager::HasAvailableTimeStamp()
{
	return FreeTimeStamps.Num() > 0;
}

int UTimeManager::DropTimeStamp()
{
	if (!HasAvailableTimeStamp())
	{
		return -1;
	}
	FTimeStamp* NewStamp = FreeTimeStamps.Pop();
	const int Id = NewStamp->TimeStampId;
	UsedTimeStamps.Add(Id, NewStamp);
	OnSaveTimeDelegate.Broadcast(Id);
	return Id;
}

void UTimeManager::LoadTimeStamp(const int &StampNumber)
{
	const float StampTime = UsedTimeStamps[StampNumber]->TimeStamp;
	CountdownTimer = StampTime;
	OnLoadTimeDelegate.Broadcast(StampNumber);
}

void UTimeManager::DeleteTimeStamp(const int &StampNumber)
{
	FTimeStamp* RemoveStamp = UsedTimeStamps[StampNumber];
	UsedTimeStamps.Remove(StampNumber);
	FreeTimeStamps.Add(RemoveStamp);
	OnDeleteTimeDelegate.Broadcast(StampNumber);
}

void UTimeManager::SetCountdownTimer(const float &TimeInMinutes)
{
	CountdownTimer = TimeInMinutes * 60.0f;
}

void UTimeManager::AddEvent(ATimeEvent* TimeEvent)
{
	const float &TriggerTime = TimeEvent->GetTriggerTime();
	if (Events.Num() == 0)
	{
		Events.AddHead(TimeEvent);
		return;
	}
	if (TriggerTime >= Events.GetHead()->GetValue()->GetTriggerTime())
	{
		Events.AddHead(TimeEvent);
		return;
	}
	if (TriggerTime <= Events.GetTail()->GetValue()->GetTriggerTime())
	{
		Events.AddTail(TimeEvent);
		return;
	}
	TDoubleLinkedList<ATimeEvent*>::TDoubleLinkedListNode* CurrentNode = Events.GetHead()->GetNextNode();
	while (CurrentNode->GetNextNode() != nullptr && CurrentNode->GetValue()->GetTriggerTime() > TriggerTime)
	{
		CurrentNode = CurrentNode->GetNextNode();
	}

	Events.InsertNode(TimeEvent, CurrentNode);
	NextTimeNode = Events.GetHead();
	NextTriggerTime = NextTimeNode->GetValue()->GetTriggerTime();
}

void UTimeManager::PausePast()
{
	bPastPaused = !bPastPaused;
}

void UTimeManager::LoadTime(const float& NewTime)
{
	CountdownTimer = NewTime;
}

void UTimeManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UTimeManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	SetCountdownTimer(UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UQuestManager>()->GetQuestTimeLimit());
	for (int i = 0; i < MaxStamps; i++)
	{
		FreeTimeStamps.Add(new FTimeStamp(i));
	}
}

void UTimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bPastPaused)
	{
		CountdownTimer -= DeltaTime;
		if (CountdownTimer <= NextTriggerTime)
		{
			while (NextTimeNode != nullptr && CountdownTimer <= NextTimeNode->GetValue()->GetTriggerTime())
			{
				NextTimeNode->GetValue()->TriggerEvent();
				NextTimeNode = NextTimeNode->GetNextNode();
			}
			if (NextTimeNode == nullptr)
			{
				NextTriggerTime = -1.0f;
			}
			else
			{
				NextTriggerTime = NextTimeNode->GetValue()->GetTriggerTime();
			}
		}
	}
}
