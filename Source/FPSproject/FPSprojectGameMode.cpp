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
	CurrentWave = 0;
	srand(time(NULL)); 
	
}
void AFPSprojectGameMode::Tick(float deltatime) 
{
	Super::Tick(deltatime);
	CurrentDelay -= deltatime;
	//UE_LOG(LogTemp, Log, TEXT("%f"), CurrentDelay); 
	
	//GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnPosition.Num)
	if (CurrentDelay < 0 && CurrentWave <= NumberOfWaves) 
	{
		for (int i = 0; i < NumberEnemiesWave; i++)
		{
			//UE_LOG(LogTemp, Log, TEXT("Je suis un spawn"));
			int pos = rand() % 4; 
			//UE_LOG(LogTemp, Log, TEXT("%d"), pos);
			
			//UE_LOG(LogTemp, Log, TEXT("%d"), SpawnPosition[pos].GetLocation().X);
			//GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnPosition[pos])
				//Set Spawn Collision Handling Override
			//FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding; 
		}
		CurrentDelay = DelayBetweenWaves;
		NumberEnemiesWave *= 2; 
		CurrentWave += 1; 

		
	}

}

