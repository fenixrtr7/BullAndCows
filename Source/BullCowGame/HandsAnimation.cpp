// Fill out your copyright notice in the Description page of Project Settings.


#include "HandsAnimation.h"

void UHandsAnimation::NativeUpdateAnimation(float Delta)
{
	//Super::NativeUpdateAnimation(Delta);

	Speed = GetOwningActor()->GetVelocity().Size() / 2000;
}
