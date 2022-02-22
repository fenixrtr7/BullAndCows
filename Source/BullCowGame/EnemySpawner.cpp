// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"



// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < Amount; i++)

	{
		int SpawnPointIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		int BlueprintIndex = FMath::RandRange(0, BlueprintsToSpawn.Num() - 1);

		if(SpawnPointIndex >= SpawnPoints.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("No hay spawn points en el spawner"));
			return;
		}

		if(BlueprintIndex >= BlueprintsToSpawn.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("No hay blueprints en el spawner"));
			return;
		}

		AActor* SpawnPoint = SpawnPoints[SpawnPointIndex];
		TSubclassOf<AActor> BlueprintToSpawn = BlueprintsToSpawn[BlueprintIndex];
		GetWorld()->SpawnActor<AActor>(BlueprintToSpawn.Get(), SpawnPoint->GetTransform());
	}
}


