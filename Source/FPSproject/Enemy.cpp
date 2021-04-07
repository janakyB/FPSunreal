// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "AIController.h"
#include "FPSprojectCharacter.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh1E = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToPLayer(DeltaTime);
	CanHit();

}

void AEnemy::MoveToPLayer(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Shoot"));
	FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector EnemyPosition = GetActorLocation();
	FVector Direction = PlayerPosition - EnemyPosition;
	float Angle = atan2(Direction.X, Direction.Y) * (180 / 3.14) * (-1);
	FRotator Rotation = { GetActorRotation().Vector().X, Angle, GetActorRotation().Vector().Z };
	SetActorRotation(Rotation);
	float Norme = Direction.Size();
	if (Norme > AttackDistance)
	{
		IsAttacking = false;
		Direction.Normalize();
		SetActorLocation(EnemyPosition + Direction * DeltaTime * MoveSpeed);
	}
	else if (Norme <= AttackDistance && CanHit())
	{
		IsAttacking = true;
		LastTimeAttack = GetGameTimeSinceCreation();
		SetActorLocation(EnemyPosition);
		AFPSprojectCharacter* player = (AFPSprojectCharacter*)GetWorld()->GetFirstPlayerController()->GetPawn();
		player->GetDamage(Damage);
		UE_LOG(LogTemp, Log, TEXT("%d"), player->CurrentLife);
	}
}
bool AEnemy::CanHit()
{
	return LastTimeAttack + CoolDown < GetGameTimeSinceCreation();
}

