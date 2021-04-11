// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSprojectCharacter.h"

#include "Gun.generated.h"

UCLASS()
class FPSPROJECT_API AGun : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FP_Gun;

	UPROPERTY(EditAnyWhere, Category = stats)
		float MaxAmmo;

	UPROPERTY(EditAnyWhere, Category = stats)
		float Damage;

	UPROPERTY(EditAnyWhere, Category = stats)
		float Reload;

	UPROPERTY(EditAnyWhere, Category = stats)
		float FireRate;

	UPROPERTY(EditAnyWhere, Category = stats)
		float ImpulseForce;

	UPROPERTY(EditAnyWhere, Category = stats)
		float NumberShoot;

	UPROPERTY(EditAnyWhere, Category = stats)
		int precision;

	UPROPERTY(EditAnyWhere, Category = stats)
		bool Automatic; 

public:
	// Sets default values for this actor's properties 
	AGun();
	USkeletalMeshComponent* GetGun();
	float GetAmmo();
	float GetDamage();
	float GetReloadTime();
	float GetFireRate();
	bool GetAutomatic(); 
	float LastTimeShoot;
	float CurrentAmmo;
	bool IsFire = false;
	FHitResult Hit;
	void SetAmmo();
	void Shoot(FVector, FVector, UParticleSystem*, UParticleSystem*);
	float RandShoot(float, float);
	bool CanShoot();
	bool CanReload();
	void Reloading();
	void DecreaseAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
