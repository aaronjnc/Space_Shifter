// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogActionInterface.h"
#include "Components/ActorComponent.h"
#include "DialogComponent.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStruct
{
	GENERATED_BODY()
	
	FString CharacterName;
	FTexture* CharacterPortrait;
};

USTRUCT(BlueprintType)
struct FDialogStruct
{
	GENERATED_BODY()
	
	FCharacterStruct Character;
	TArray<UDialogActionInterface*> DialogActions;
	FString Sentence;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACE_SHIFTER_API UDialogComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TArray<AActor*> StartDialogActions;
	UPROPERTY(EditAnywhere, Category = "Dialog")
	TArray<AActor*> EndDialogActions;
	UPROPERTY(EditAnywhere, Category = "Dialog")
	TArray<FDialogStruct> DialogStructs;

public:	
	// Sets default values for this component's properties
	UDialogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
