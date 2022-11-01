// Fill out your copyright notice in the Description page of Project Settings.


#include "RicochetEffect.h"
#include "GameFramework/ProjectileMovementComponent.h"

void URicochetEffect::ActivateHitEffect()
{
	Super::ActivateHitEffect();
	if (Projectile)
	{
		RicoHits--;

		if (RicoHits <= 0)
			Projectile->OnProjectileDestroy();

		FVector Vel = Projectile->GetProjectileMovement()->Velocity;


		Projectile->GetProjectileMovement()->Velocity = -Vel;
	}
}

