// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileEffectComponent.h"
#include "RicochetEffect.generated.h"

/**
 * 
 */
UCLASS()
class HYPERDRIVE_API URicochetEffect : public UProjectileEffectComponent
{
	GENERATED_BODY()

private:
	int RicoHits = 5;

public:

	virtual void ActivateHitEffect() override;
	
};
