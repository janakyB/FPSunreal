// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"

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
void AGun::Shoot(FVector StartLocation, FVector EndLocation, UParticleSystem* FireParticule, UParticleSystem* OutParticle)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireParticule, GetGun()->GetSocketTransform((FName("Muzzle"))));
	for (int i = 0; i < NumberShoot; i++)
	{
		float Y = RandShoot(-precision, precision);
		float Z = RandShoot(-precision, precision);
		FVector RandomVector = { EndLocation.X, EndLocation.Y + Y, EndLocation.Z + Z };
		GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, RandomVector, ECC_Visibility);
		FVector ImpulseDir = { Hit.ImpactPoint.X - StartLocation.X, Hit.ImpactPoint.Y - StartLocation.Y, Hit.ImpactPoint.Z - StartLocation.Z };
		ImpulseDir.Normalize();
		ImpulseDir *= ImpulseForce;
		if (Hit.IsValidBlockingHit() == true)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OutParticle, Hit.ImpactPoint);
			Hit.GetComponent()->AddImpulseAtLocation(ImpulseDir * 100000, Hit.ImpactPoint);
			if (Hit.GetActor()->GetName().Contains("BP_Enemy"))
			{
				AEnemy* enemy = (AEnemy*)Hit.GetActor();
				enemy->GetDamage(Damage);
			}
		}
	}




}
float AGun::RandShoot(float a, float b)
{
	float nRand;
	nRand = a + ((float)rand() * (b - a + 1) / (RAND_MAX - 1));
	return nRand;
}
