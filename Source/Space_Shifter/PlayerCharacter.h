// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UPortal;
class UGrabber;
class AInteractable;
class UPhysicsHandleComponent;
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

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UGrabber> GrabberComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandleComponent;

	UPROPERTY(EditAnywhere, Category = "Shifting")
	FName FutureStartTag;

	UPROPERTY(EditAnywhere, Category = "Shifting")
	FName PastStartTag;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float InteractDistance;

	FVector FutureStartPosition;

	FVector PastStartPosition;

	bool bInTheFuture;

	bool bPortalActive;

	TWeakObjectPtr<AInteractable> InteractObject;

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
	
	void Interact();

	void ShiftTime();

	void PortalAction();

	UCameraComponent* GetCameraComponent();

private:
	
	void ActivatePortal();

	void DeactivatePortal();

	void UpdateCaptureLocation();

};
