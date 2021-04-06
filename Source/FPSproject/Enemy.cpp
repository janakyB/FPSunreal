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

}

void AEnemy::MoveToPLayer(float DeltaTime) 
{
	//UE_LOG(LogTemp, Log, TEXT("Shoot"));
	
	
	FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector EnemyPosition = GetActorLocation();
	FVector EndPpositionEnemyRayCast = EnemyPosition + GetActorLocation().ForwardVector * 10000;
	FVector Direction = PlayerPosition - EnemyPosition;
	float Norme = Direction.Size();
	if (Norme <= AttackDistance /*&& CanHit()*/) 
	{
		IsAttacking = true;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("JE SUIS mort")));
		LastTimeAttack = GetGameTimeSinceCreation();  
		SetActorLocation(EnemyPosition);  
		//bool bHit = GetWorld()->LineTraceSingleByChannel(hit, EnemyPosition, EndPpositionEnemyRayCast, ECC_Visibility);
		/*AFPSprojectCharacter* player = (AFPSprojectCharacter)GetWorld()->GetFirstPlayerController(); 
		if (bHit) {
			FString name = hit.GetActor()->GetName(); 
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("%s"), name));
			
			if (hit.GetActor()->GetName().Contains("FirstPersonCharacter2_C_O"))
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("JAB")));
			}

			if (hit.GetActor()->GetName().Contains("FirstPerson"))
			{

				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("JAC")));
				AFPSprojectCharacter* player = (AFPSprojectCharacter*)hit.GetActor();
				player->GetDamage(Damage);
			}
		}*/
		
	}
	else 
	{
		IsAttacking = false; 
		
		Direction.Normalize();
		SetActorLocation(EnemyPosition + Direction * DeltaTime * MoveSpeed);
		float Angle = atan2(Direction.X, Direction.Y) * (180 / 3.14) * (-1);
		FRotator Rotation = { GetActorRotation().Vector().X, Angle, GetActorRotation().Vector().Z };
		SetActorRotation(Rotation);
	}
}
bool AEnemy::CanHit() 
{
	return LastTimeAttack + CoolDown > GetGameTimeSinceCreation(); 
}

