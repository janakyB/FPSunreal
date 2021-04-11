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
	CharacterList.Add((AFPSprojectCharacter*)GetWorld()->GetFirstPlayerController()->GetPawn()); 
	srand(time(NULL));

}
void AFPSprojectGameMode::Tick(float deltatime)
{
	Super::Tick(deltatime);
	CurrentDelay -= deltatime; 
	EnemyDeath(deltatime); 
	DestroyEnemy(); 
	
	UE_LOG(LogTemp, Log, TEXT("%d"), CharacterList[0]->CurrentLife);

	if (CharacterList[0]->CurrentLife <= 0)
	{

		UE_LOG(LogTemp, Log, TEXT("Je suis un chat"));
		DeathAndRespawn();
	}
	
	//GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnPosition.Num)
	if (CurrentDelay < 0 && CurrentWave <= NumberOfWaves)
	{
		Spawn = true;
		CurrentDelayEnnemies -= deltatime;
		if (CurrentDelayEnnemies < 0 && Count <= NumberEnemiesWave && Spawn == true)
		{

			int pos = rand() % 4;
			AEnemy* newEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnPosition[pos]);
			EnemyList.Add(newEnemy); 
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
void AFPSprojectGameMode::DeathAndRespawn()
{
	UE_LOG(LogTemp, Log, TEXT("Je suis un chat"));
	for  (int i = 0; i < EnemyList.Num();  i++)
	{
		EnemyList[i]->Destroy(); 
	}
	EnemyList.Empty();
	CurrentDelay = DelayBetweenWaves;
	CurrentDelayEnnemies = DelayBetweenEnemies;
	Count = 0; 
	Spawn = false;
	CurrentWave = 0;
	NumberEnemiesWave = 5; 
	CharacterList[0]->DeathAndRespawn();
	CharacterList[0]->SetActorLocation(playerespawn.GetLocation());
}
void AFPSprojectGameMode::DestroyEnemy()
{
	for (int i = 0; i < EnemyList.Num(); i++)
	{
		if (EnemyList[i]->Death == true && EnemyList[i]->DelayDeath < 0)
		{
			EnemyList[i]->Destroy();
			EnemyList.RemoveSingle(EnemyList[i]);
			/*for (int j = i + 1; j < EnemyList.Num() - j; j++)
			{
				EnemyList[j] = EnemyList[j - 1]; 
			}*/
			
		}
	}
}
void AFPSprojectGameMode::EnemyDeath(float DeltaTime)
{
	for (int i = 0; i < EnemyList.Num(); i++)
	{
		if (EnemyList[i]->Death == true)
		{
			EnemyList[i]->DelayDeath -= DeltaTime;
		}
	}
	
}

