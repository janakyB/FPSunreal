// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSprojectGameMode.h"
#include "FPSprojectHUD.h"
#include "FPSprojectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"
#include "stdlib.h"
#include "time.h"

AFPSprojectGameMode::AFPSprojectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSprojectHUD::StaticClass();
	PrimaryActorTick.bCanEverTick = true; 
}

void AFPSprojectGameMode::BeginPlay() 
{
	Super::BeginPlay(); 
	CurrentDelay = DelayBetweenWaves;
	CurrentDelayEnnemies = DelayBetweenEnemies; 
	CurrentWave = 0;
	srand(time(NULL)); 
	
}
void AFPSprojectGameMode::Tick(float deltatime) 
{
	Super::Tick(deltatime);
	CurrentDelay -= deltatime;

	
	//GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnPosition.Num)
	if (CurrentDelay < 0 && CurrentWave <= NumberOfWaves) 
	{
		Spawn = true; 
		CurrentDelayEnnemies -= deltatime; 
		if (CurrentDelayEnnemies < 0 && Count <= NumberEnemiesWave && Spawn == true) 
		{
			
			int pos = rand() % 4;
			AEnemy* newEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnPosition[pos]);
			Count++;
			CurrentDelayEnnemies = DelayBetweenEnemies; 
		}
		else if (Count > NumberEnemiesWave)
		{
			Count = 0; 
			Spawn = false; 
			CurrentDelay = DelayBetweenWaves; 
			NumberEnemiesWave *= 2; 
			CurrentWave++; 
		}
	}
}


