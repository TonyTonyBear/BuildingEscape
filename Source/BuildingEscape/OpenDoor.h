// Copyright Tony Barrett, 2020.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

// Door Opening Behaviours
UENUM(BlueprintType)
enum class EDoorOpenBehaviorEnum : uint8
{
	EBehaviourRotate UMETA(DisplayName="Rotate Around Pivot"),
	EBehaviourTranslate UMETA(DisplayName="Translate to a new Location"),
};

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
	void CacheComponents();
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float CalculateTotalMassInsideTrigger() const;

	UPROPERTY(EditAnywhere)
	TArray<ATriggerVolume*> PressurePlates;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float TargetYaw = -90.f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float MassThreshold = 50.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;

	UPROPERTY(EditAnywhere)
	FVector TargetRelativeLocation;

	UPROPERTY(EditAnywhere)
	EDoorOpenBehaviorEnum DoorBehaviour;

	float DoorLastOpened = 0.f;
	float StartingYaw;
	FVector StartingLocation;

	bool bOpeningSoundHasPlayed = false;
	bool bClosingSoundHasPlayed = true;
};
