// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Space_Shifter/Interactables/Interactable.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent()) {
		PhysicsHandle->SetTargetLocationAndRotation(GetComponentLocation() + GetForwardVector() * HoldDistance, GetComponentRotation());
	}
}

void UGrabber::Grab(AInteractable* Interactable) 
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Valid handle"));
	UPrimitiveComponent* HitComponent = Interactable->GetMesh();
	HitComponent->SetSimulatePhysics(true);
	Interactable->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	HitComponent->WakeAllRigidBodies();
	Interactable->Tags.Add("Grabbed");
	PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, Interactable->GetActorLocation(), GetComponentRotation());
	bIsGrabbing = true;
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
		return;
	UPrimitiveComponent* GrabComponent = PhysicsHandle->GetGrabbedComponent();
	if (GrabComponent == nullptr)
		return;
	GrabComponent->GetOwner()->Tags.Remove("Grabbed");
	PhysicsHandle->ReleaseComponent();
	bIsGrabbing = false;
}

bool UGrabber::GetIsGrabbing()
{
	return bIsGrabbing;
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const 
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}
	return Result;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);
}