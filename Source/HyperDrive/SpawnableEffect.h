// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileEffectComponent.h"
#include "SpawnableEffect.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HYPERDRIVE_API USpawnableEffect : public UProjectileEffectComponent
{
	GENERATED_BODY()
public:
	USpawnableEffect();

	virtual void ActivateHitEffect() override;

	virtual void ActivatePawnResponse() override;

	virtual void ActivateDestroyEffect() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable | Effect Properties")
		TSubclassOf<AActor> HitSpawnObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable | Effect Properties")
		TSubclassOf<AActor> PawnHitSpawnObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable | Effect Properties")
		TSubclassOf<AActor> DestroySpawnObject;

};
