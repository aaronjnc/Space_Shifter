// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogActionInterface.h"
#include "Components/ActorComponent.h"
#include "DialogComponent.generated.h"

UENUM(BlueprintType)
enum EDialogAction
{
	Default,
};

USTRUCT(BlueprintType)
struct FCharacterStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* CharacterPortrait;
};

USTRUCT(BlueprintType)
struct FDialogStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EDialogAction>> SentenceDialogEnums;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
	TMap<TEnumAsByte<EDialogAction>, UDialogActionInterface*> SentenceDialogActions;
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
