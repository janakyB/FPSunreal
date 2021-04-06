// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class FPSPROJECT_API AEnemy : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1E;
	
public:	
	// Sets default values for this actor's properties
	AEnemy();
	void MoveToPLayer(float Deltatime); 
	bool CanHit(); 
	float MoveSpeed = 200.0f; 
	bool IsAttacking = false; 
	float AttackDistance = 300.f; 
	float LastTimeAttack = 0.0f; 
	float CoolDown = 5.0f; 
	float Damage = 1.0f; 
	FHitResult hit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
