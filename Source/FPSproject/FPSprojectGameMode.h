// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSprojectCharacter.h"
#include "FPSprojectGameMode.generated.h"

UCLASS(minimalapi)
class AFPSprojectGameMode : public AGameModeBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnyWhere, Category = Transform)
		TArray < FTransform > SpawnPosition;

	UPROPERTY(EditDefaultsOnly, Category = Enemy)
		TSubclassOf<class AEnemy> EnemyClass;

	UPROPERTY(EditDefaultsOnly, Category = PlayerRespawn)
		FTransform playerespawn;
public:
	AFPSprojectGameMode();
	void WaveManager();
	bool DelaySpawnEnemy();
	void DeathAndRespawn();
	void DestroyEnemy();
	void EnemyDeath(float);
	//AFPSprojectCharacter* player;
	int NumberOfWaves = 5;
	int NumberEnemiesWave = 5;
	float DelayBetweenWaves = 20.0f;
	float CurrentDelay;
	int CurrentWave;
	float DelayBetweenEnemies = 1.0f;
	float CurrentDelayEnnemies;
	int Count = 0;
	bool PlayerIsDead = false;
	TArray <AEnemy*> EnemyList;
	TArray <AFPSprojectCharacter*> CharacterList;
	bool Spawn;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float deltatime) override;
};



