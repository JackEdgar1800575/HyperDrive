// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ProjectileActor.h"
#include "ProjectileEffectComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HYPERDRIVE_API UProjectileEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectileEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AProjectileActor* Projectile;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ActivateHitEffect();

	void SetProjectile(AProjectileActor* InProj) { Projectile = InProj; };
		
};
