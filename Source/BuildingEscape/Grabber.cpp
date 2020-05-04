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

	// Cache Attached Components
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandleComponent could not be found on %s. Verify that component is attached to actor."), *(GetOwner()->GetName()));
	}

	if (InputComponent)
	{
		// Bind Actions
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent could not be found on %s. Verify that component is attached to actor."), *(GetOwner()->GetName()));
	}
	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbing..."));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Releasing..."));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player viewpoint
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

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
	FHitResult Hit;
	FCollisionQueryParams QueryParams(TEXT(""), false, GetOwner()); // We aren't naming this trace, we aren't using visiblity collisions, and we're ignoring any hits on whatever has this component attached.

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		QueryParams
	);

	AActor* HitActor = Hit.GetActor();

	if(HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s was found by line trace."), *(HitActor->GetName()));
	}
}

