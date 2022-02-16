// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HandsAnimation.generated.h"

/**
 * 
 */
UCLASS()
class BULLCOWGAME_API UHandsAnimation : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float Speed;
	
	void NativeUpdateAnimation(float delta) override;
};
