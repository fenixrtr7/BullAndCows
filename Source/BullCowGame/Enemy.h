// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class BULLCOWGAME_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere)
	float Life = 100;
	

};
