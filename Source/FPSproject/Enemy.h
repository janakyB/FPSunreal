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
	UPROPERTY(EditDefaultsOnly, Category = animation)
		UAnimSequence* animIdle;
	UPROPERTY(EditDefaultsOnly, Category = animation)
		UAnimSequence* animWalk;
	UPROPERTY(EditDefaultsOnly, Category = animation)
		UAnimSequence* animAttack;
	UPROPERTY(EditDefaultsOnly, Category = animation)
		UAnimSequence* animDeath;
public:
	// Sets default values for this actor's properties
	AEnemy();
	void MoveToPLayer(float Deltatime);
	bool CanHit();
	void GetDamage(float);
	void Dead();
	float MoveSpeed = 150.0f;
	bool IsAttacking = false;
	bool Death = false;
	float AttackDistance = 300.f;
	float LastTimeAttack = 0.0f;
	float CoolDown = 5.0f;
	float Damage = 1.0f;
	FHitResult hit;
	float MaxLife = 5;
	float CurrentLife;
	float DelayDeath = 3.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
