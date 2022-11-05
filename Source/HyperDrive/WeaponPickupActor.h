// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupActor.h"
#include "WeaponPickupActor.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HYPERDRIVE_API AWeaponPickupActor : public APickupActor
{
	GENERATED_BODY()

public:
	AWeaponPickupActor();

	virtual void PickupResponse(AHyperDrivePawn* Player) override;


	UPROPERTY(Category = "Pickup", BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AWeaponActor> NewWeapon;
	
};
