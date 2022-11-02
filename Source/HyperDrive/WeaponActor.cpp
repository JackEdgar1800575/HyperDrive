// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"
//#include "Sound/SoundBase.h"
#include "../Plugins/Wwise/Source/AkAudio/Classes/AkGameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileActor.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FireRate = 0.1f;
	bCanFire = true;
	MaxAmmo = 20;
	AmmoCount = MaxAmmo;
	ProjectileStrength = -1;
	WeaponRange = 5000.0f;
	bIsInfiniteAmmo = false;
	DamageAmount = 500;

}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	bCanFire = true;
	
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::Fire(FVector SpawnPosition, FRotator Rotation)
{
	// If it's ok to fire again
	if (bCanFire == true && (AmmoCount > 0 || bIsInfiniteAmmo))
	{

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			FTransform SpawnTM(Rotation, SpawnPosition);
			AProjectileActor* Launched = Cast<AProjectileActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileType, SpawnTM));
			if (Launched)
			{
				// spawn the projectile
				Launched->DamageAmount = DamageAmount;
				Launched->ProjectileStrength = ProjectileStrength;
				Launched->Range = WeaponRange;

				UGameplayStatics::FinishSpawningActor(Launched, SpawnTM);
			}
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AWeaponActor::ShotTimerExpired, FireRate);

		//Play Audio of Weapon Firing
		if (WeaponFireEvent != nullptr)
		{
			PlayingID = FAkAudioDevice::Get()->PostEvent(WeaponFireEvent, this);

		}

		bCanFire = false;
		if (!bIsInfiniteAmmo)
		{
			AmmoCount--;
		}
	}
}

void AWeaponActor::Reload()
{
}

void AWeaponActor::ShotTimerExpired()
{
	bCanFire = true;
}
