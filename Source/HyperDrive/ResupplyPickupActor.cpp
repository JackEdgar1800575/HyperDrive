// Fill out your copyright notice in the Description page of Project Settings.


#include "ResupplyPickupActor.h"

AResupplyPickupActor::AResupplyPickupActor()
{
	PickupValue = 50;
	bIsFull = false;
	Type = EResupplyType::HEALTH;
}

