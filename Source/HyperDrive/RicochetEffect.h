// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileEffectComponent.h"
#include "RicochetEffect.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HYPERDRIVE_API URicochetEffect : public UProjectileEffectComponent
{
	GENERATED_BODY()
public:
	URicochetEffect();

private:
	int RicoHits = 5;

public:

	virtual void ActivateHitEffect() override;

	virtual void ActivateDestroyEffect() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
		int MaxRicos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
		float RicoSpeedChange;



};
