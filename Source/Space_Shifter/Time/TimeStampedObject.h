// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeStampedObject.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SPACE_SHIFTER_API UTimeStampedObject : public UObject
{
	GENERATED_BODY()

public:

	virtual void OnSaveTimeStamp(int TimeStamp);

	virtual void OnLoadTimeStamp(int TimeStamp);

	virtual void OnDeleteTimeStamp(int TimeStamp);

protected:

	virtual void SetupListeners();

};
