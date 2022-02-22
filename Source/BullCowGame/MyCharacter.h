// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class BULLCOWGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	FTimerHandle ShootTimerHandle; 

	void MoveForward(float value);
	void MoveRight(float value);
	void RotateYaw(float value);
	void RotatePitch(float value);
	void StartJump();
	void StopJump();
	void StartShoot();
	void StopShoot();

	void ShootTimer();
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Cam;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Arms;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Gun;

	UPROPERTY(EditAnywhere)
	TMap<FName, float> Damages;
	
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 45;

	UPROPERTY(EditAnywhere)
	float BaseDamage = 20;
	
	AMyCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
