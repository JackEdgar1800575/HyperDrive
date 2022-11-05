// Fill out your copyright notice in the Description page of Project Settings.


#include "ResupplyPickupActor.h"

AResupplyPickupActor::AResupplyPickupActor()
{
	PickupValue = 50;
	bIsFull = false;
	Type = EResupplyType::HEALTH;
}

void AResupplyPickupActor::PickupResponse(AHyperDrivePawn* Player)
{
	if (Type == EResupplyType::HEALTH)
	{
		if (!bIsFull)
			Player->CurrentHealth += PickupValue;
		else
			Player->CurrentHealth = Player->MaxHealth;
		PlayPickupSound();
		Destroy();
	}

	if (Type == EResupplyType::ARMOUR)
	{
		if (!bIsFull)
			Player->CurrentArmour += PickupValue;
		else
			Player->CurrentArmour = Player->MaxArmour;
		PlayPickupSound();
		Destroy();

	}
}

