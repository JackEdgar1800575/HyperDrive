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

	UFUNCTION(BlueprintCallable)
	virtual void ActivateHitEffect();

	UFUNCTION(BlueprintCallable)
	virtual void ActivatePawnResponse();

	UFUNCTION(BlueprintCallable)
	virtual void ActivateDestroyEffect();

	UFUNCTION(BlueprintCallable)
	void SetProjectile(AProjectileActor* InProj) { Projectile = InProj; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
		bool bIsSticky = false;
	//Flag to specify whether the same effect should play on hit as well as destroy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
		bool bHitActionOnDestroy = false;
	//Signals whether the projectile has a unique destroy effect or not. If false, projectile is simply destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
		bool bAutoDestroy = true;
	//Flag to determine whether hitting a pawn has a unique response compared to when hitting anything else
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Properties")
		bool bUniquePawnResponse = false;

		
};
