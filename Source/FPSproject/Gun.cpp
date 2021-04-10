// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmo;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
USkeletalMeshComponent* AGun::GetGun()
{
	return FP_Gun;
}
float AGun::GetAmmo()
{
	return CurrentAmmo;
}
float AGun::GetDamage()
{
	return Damage;
}
float AGun::GetReloadTime()
{
	return Reload;
}
float AGun::GetFireRate()
{
	return FireRate;
}
void AGun::SetAmmo()
{
	CurrentAmmo = MaxAmmo;
}
bool AGun::CanShoot()
{
	return LastTimeShoot + FireRate < GetGameTimeSinceCreation();
}
bool AGun::CanReload()
{
	return LastTimeShoot + Reload < GetGameTimeSinceCreation();
}
void AGun::Reloading()
{
	if (CanReload())
	{
		SetAmmo();
	}
}
void AGun::DecreaseAmmo()
{
	CurrentAmmo--;
	LastTimeShoot = GetGameTimeSinceCreation();
}

