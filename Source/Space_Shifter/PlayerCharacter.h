// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UPortal;
struct FInputActionValue;
UCLASS()
class SPACE_SHIFTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPortal> PortalComponent;

	UPROPERTY(EditAnywhere, Category = "Shifting")
	FName FutureStartTag;

	UPROPERTY(EditAnywhere, Category = "Shifting")
	FName PastStartTag;

	FVector FutureStartPosition;

	FVector PastStartPosition;

	bool bInTheFuture;

	bool bPortalActive;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void ShiftTime();

	void PortalAction();

private:
	
	void ActivatePortal();

	void DeactivatePortal();

	void UpdateCaptureLocation();

};
