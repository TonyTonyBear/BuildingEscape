// Copyright Tony Barrett, 2020.

#include "Grabber.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

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

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player viewpoint
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	// Log out parameters.
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s\nRotation: %s"), *PlayerLocation.ToString(), *PlayerRotation.ToString());

	// Raycast out some distance.
	FVector LineTraceEnd = PlayerLocation + (PlayerRotation.Vector() * Reach);

	DrawDebugLine(
		GetWorld(), 
		PlayerLocation, 
		LineTraceEnd, 
		FColor::Green, 
		false, 
		0.f, 
		0, 
		5.f
	);

	// Report back on what was hit.
}

