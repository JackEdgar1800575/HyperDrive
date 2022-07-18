// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupActor.h"
#include "ResupplyPickupActor.generated.h"

/**
 * 
 */

UENUM(Blueprintable)
enum class EResupplyType : uint8
{
	HEALTH  UMETA(DisplayName = "Health"),
	ARMOUR UMETA(DisplayName = "Armour"),
	COIN UMETA(DisplayName = "Coin"),
	ENERGY UMETA(DisplayName = "Energy"),
	AMMO UMETA(DisplayName = "Ammo")
};

UCLASS(Blueprintable)
class HYPERDRIVE_API AResupplyPickupActor : public APickupActor
{
	GENERATED_BODY()

public:
	AResupplyPickupActor();
	//The value that the pickup is worth
	UPROPERTY(Category = "Pickup", BlueprintReadWrite, EditAnywhere)
		int PickupValue;
	//Controls whether the pickup will resupply by an ammount or in full
	UPROPERTY(Category = "Pickup", BlueprintReadWrite, EditAnywhere)
		bool bIsFull;
	//Player property that the pickup is intended to resupply
	UPROPERTY(Category = "Pickup", BlueprintReadWrite, EditAnywhere)
		EResupplyType Type;

	
};
