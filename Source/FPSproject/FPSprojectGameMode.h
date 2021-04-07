// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSprojectGameMode.generated.h"

UCLASS(minimalapi)
class AFPSprojectGameMode : public AGameModeBase
{
	GENERATED_BODY()
		UPROPERTY(EditAnyWhere, Category = Transform)
		FTransform SpawnPosition; 

	UPROPERTY(EditDefaultsOnly, Category = Enemy)
	TSubclassOf<class AEnemy> EnemyClass;
public:
	AFPSprojectGameMode();
	void WaveManager();
	void SpawnEnemy(FTransform); 
	int NumberOfWaves = 5; 
	int NumberEnemiesWave = 5; 
	float DelayBetweenWaves = 5.0f; 
	float CurrentDelay; 
	int CurrentWave; 
	float DelayBetweenEnemies = 3.0f; 
protected: 
	virtual void BeginPlay() override; 
public : 
	virtual void Tick(float deltatime) override; 
};



