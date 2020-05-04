// Copyright Tony Barrett, 2020.


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += StartingYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has an OpenDoor component attached, but PressurePlate is not set."), *GetOwner()->GetName());
	}

	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float CurrentGameTime = GetWorld()->GetTimeSeconds();

	if (CalculateTotalMassInsideTrigger() >= MassThreshold)
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
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, OpenSpeed);
	GetOwner()->SetActorRotation(CurrentRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, StartingYaw, DeltaTime, OpenSpeed);
	GetOwner()->SetActorRotation(CurrentRotation);
}

float UOpenDoor::CalculateTotalMassInsideTrigger() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (int i = 0; i < OverlappingActors.Num(); i++)
	{
		TotalMass += OverlappingActors[i]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

