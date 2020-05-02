// Copyright Tony Barrett, 2020.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		OpenDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, OpenSpeed);
	GetOwner()->SetActorRotation(CurrentRotation);
}

