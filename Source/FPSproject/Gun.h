// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	
public:	
	// Sets default values for this actor's properties 
	AGun();
	USkeletalMeshComponent* GetGun(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
