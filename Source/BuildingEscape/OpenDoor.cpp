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
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// FRotator CurrentRotation = GetOwner()->GetActorRotation();
	// CurrentRotation.Yaw = -90.f;
	// GetOwner()->SetActorRotation(CurrentRotation);

	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	UE_LOG(LogTemp, Warning, TEXT("The current yaw of the door is: %f"), CurrentYaw);

	// Lerp the door this frame. - NOTE: THIS IS NOT LERPING. THIS IS USING AN EXPONENTIAL VERSION.
	FRotator OldRotation = GetOwner()->GetActorRotation();
	FRotator TargetRotation = OldRotation;

	TargetRotation.Yaw = TargetYaw;
	
	FRotator CurrentRotation = FMath::Lerp(OldRotation, TargetRotation, 0.1f);

	GetOwner()->SetActorRotation(CurrentRotation);
}

