// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS(Blueprintable)
class HYPERDRIVE_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Weapon Actions
	virtual void Fire(FVector SpawnPosition, FRotator Rotation);
	virtual void Reload();

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	//Weapon Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Components")
		TSubclassOf<class AProjectileActor> ProjectileType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Components")
	//	class UAkAudioEvent* WeaponFireEvent;

	//Weapon Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	int MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float ReloadSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	int DamageAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	int ProjectileStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float WeaponRange;

	//Weapon Condition
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Current State")
	int AmmoCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current State")
	bool bIsInfiniteAmmo;

private:
	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	FTimerHandle TimerHandle_ReloadTimer;

};
