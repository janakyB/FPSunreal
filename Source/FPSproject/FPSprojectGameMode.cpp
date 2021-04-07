// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSprojectGameMode.h"
#include "FPSprojectHUD.h"
#include "FPSprojectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"

AFPSprojectGameMode::AFPSprojectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSprojectHUD::StaticClass();
}

void AFPSprojectGameMode::BeginPlay() 
{
	Super::BeginPlay(); 
	CurrentDelay = DelayBetweenWaves; 
}
void AFPSprojectGameMode::Tick(float deltatime) 
{
	Super::Tick(deltatime);
	CurrentDelay -= deltatime;
	if (CurrentDelay <= 0) 
	{
		CurrentDelay = DelayBetweenWaves;
		while (CurrentEnemy <= NumberEnemiesWave) 
		{
			WaveManager(); 
		}
		
	}

}
void AFPSprojectGameMode::WaveManager()
{
	FTransform tempPos; 
	int pos = rand() % 4; 
	for (int i = 0; i < sizeof(SpawnPosition); i++)
	{
		if (i == pos) 
		{
			tempPos = SpawnPosition[i];
			SpawnEnemy(tempPos); 
		}
	}

}
void AFPSprojectGameMode::SpawnEnemy(FTransform Position) 
{
	GetWorld()->SpawnActor<AEnemy>(EnemyClass, Position); 
}
