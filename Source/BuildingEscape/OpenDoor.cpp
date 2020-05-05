// Copyright Tony Barrett, 2020.


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	// TODO: Break this into its own function.
	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += StartingYaw;
	StartingLocation = GetOwner()->GetActorLocation();
	TargetRelativeLocation += StartingLocation;

	CacheComponents();
}

void UOpenDoor::CacheComponents()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find AudioComponent. Make sure it is attached to %s"), *(GetOwner()->GetName()));
	}

	if (PressurePlates.Num() < 1)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has an OpenDoor component attached, but PressurePlate is not set."), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float CurrentGameTime = GetWorld()->GetTimeSeconds();

	if (bShouldForceDoorOpen || (CalculateTotalMassInsideTrigger() >= MassThreshold))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = CurrentGameTime;
	}
	else if (CurrentGameTime >= DoorLastOpened + DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}
	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	if (DoorBehaviour == EDoorOpenBehaviorEnum::EBehaviourRotate)
	{
		FRotator CurrentRotation = GetOwner()->GetActorRotation();
		CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, OpenSpeed);
		GetOwner()->SetActorRotation(CurrentRotation);
	}
	else
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		CurrentLocation = FMath::VInterpTo(CurrentLocation, TargetRelativeLocation, DeltaTime, OpenSpeed);
		GetOwner()->SetActorLocation(CurrentLocation);
	}
	

	if (AudioComponent && !bOpeningSoundHasPlayed)
	{
		AudioComponent->Play();
		bOpeningSoundHasPlayed = true;
		bClosingSoundHasPlayed = false;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	if (DoorBehaviour == EDoorOpenBehaviorEnum::EBehaviourRotate)
	{
		FRotator CurrentRotation = GetOwner()->GetActorRotation();
		CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, StartingYaw, DeltaTime, OpenSpeed);
		GetOwner()->SetActorRotation(CurrentRotation);
	}
	else
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		CurrentLocation = FMath::VInterpTo(CurrentLocation, StartingLocation, DeltaTime, OpenSpeed);
		GetOwner()->SetActorLocation(CurrentLocation);
	}

	if (AudioComponent && !bClosingSoundHasPlayed)
	{
		AudioComponent->Play();
		bOpeningSoundHasPlayed = false;
		bClosingSoundHasPlayed = true;
	}
}

float UOpenDoor::CalculateTotalMassInsideTrigger() const
{
	float TotalMass = 0.f;
	TArray<AActor*> TotalOverlaps;
	TArray<AActor*> PlateOverlaps;

	if (PressurePlates.Num() < 1) return -1.f;

	for (ATriggerVolume* Volume : PressurePlates)
	{
		Volume->GetOverlappingActors(OUT PlateOverlaps);
		TotalOverlaps.Append(PlateOverlaps);	
	}

	for (int i = 0; i < TotalOverlaps.Num(); i++)
	{
		TotalMass += TotalOverlaps[i]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

