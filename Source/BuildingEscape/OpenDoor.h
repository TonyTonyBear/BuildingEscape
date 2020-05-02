// Copyright Tony Barrett, 2020.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float TargetYaw = -90.f;
	float StartingYaw;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = 2.f;

	AActor* ActorThatOpensDoor;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;
};
