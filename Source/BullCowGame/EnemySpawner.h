// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class BULLCOWGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int Amount = 1;
	
	UPROPERTY(EditAnywhere)
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> BlueprintsToSpawn;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
