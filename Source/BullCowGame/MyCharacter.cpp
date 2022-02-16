// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"


AMyCharacter::AMyCharacter()
{
	Cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	Cam->bUsePawnControlRotation = true;
	Cam->SetupAttachment(GetRootComponent());

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
	Arms->SetupAttachment(Cam);

	Gun = CreateDefaultSubobject<USkeletalMeshComponent>("Gun");
	Gun->SetupAttachment(Arms, "GripPoint");
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::RotateYaw);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::RotatePitch);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::StartShoot);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyCharacter::StopShoot);
}

void AMyCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AMyCharacter::RotateYaw(float value)
{
	AddControllerYawInput(value * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::RotatePitch(float value)
{
	AddControllerPitchInput(value * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::StartJump()
{
	Jump();
}

void AMyCharacter::StopJump()
{
	StopJumping();
}

void AMyCharacter::StartShoot()
{
	GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &AMyCharacter::ShootTimer,0.267, true);
}

void AMyCharacter::StopShoot()
{
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
}

void AMyCharacter::ShootTimer()
{
	FHitResult HitInfo;
	bool bHasHit = GetWorld()->LineTraceSingleByChannel(HitInfo, Cam->GetComponentLocation(), Cam->GetComponentLocation() + Cam->GetForwardVector() * 1000, ECC_GameTraceChannel3);
	
	DrawDebugLine(GetWorld(), Cam->GetComponentLocation(), Cam->GetComponentLocation() + Cam->GetForwardVector() * 1000, FColor::Red, false, 3);

	UE_LOG(LogTemp, Warning, TEXT("Bone Name: %s"), *HitInfo.BoneName.ToString());
	
	if(bHasHit && HitInfo.GetActor())
	{
		//HitInfo.GetActor()->Destroy();
		
	}
}



