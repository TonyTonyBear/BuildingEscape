// Copyright Tony Barrett, 2020.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float CalculateTotalMassInsideTrigger() const;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float TargetYaw = -90.f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float MassThreshold = 50.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;

	float DoorLastOpened = 0.f;
	float StartingYaw;
};
