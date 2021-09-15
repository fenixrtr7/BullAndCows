// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLCOWGAME_API UOpenDoor : public UActorComponent
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
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void FindPressurePlate();

	// Tracks whether the sound has been played.
	bool OpenDoorSound = false;
	bool CloseDoorSound = true;
	
	private:

	float InitialYaw;
	float CurrentYaw;
	
	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.0f;
	
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;
	
	float DoorLastOpened = 0.0f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.0f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 2.0f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 3.0f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};