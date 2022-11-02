// Fill out your copyright notice in the Description page of Project Settings.


#include "RicochetEffect.h"
#include "GameFramework/ProjectileMovementComponent.h"

URicochetEffect::URicochetEffect()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxRicos = 5;
    RicoHits = MaxRicos;
	RicoSpeedChange = 1.0f;

}

void URicochetEffect::ActivateHitEffect()
{
	Super::ActivateHitEffect();
	if (Projectile)
	{
		RicoHits--;

		if (RicoHits <= 0)
			Projectile->OnProjectileDestroy();

		FVector Vel = Projectile->GetProjectileMovement()->Velocity;
		Vel *= -RicoSpeedChange;

		Projectile->GetProjectileMovement()->Velocity = Vel;
	}
}

