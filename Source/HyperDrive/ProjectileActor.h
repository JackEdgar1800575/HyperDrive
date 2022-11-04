// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

class UProjectileEffectComponent;
UCLASS(Blueprintable)
class HYPERDRIVE_API AProjectileActor : public AActor
{
	GENERATED_BODY()

	//Projectile mesh used for collision and visualise projectile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileEffectComponent* ProjectileSpecialComponent;
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///** Function to handle the projectile hitting something */
	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		virtual void OnProjectileDestroy();

	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int DamageAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int ProjectileStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float ProjectileSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float Range;

	//Projectile Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<UProjectileEffectComponent> ProjectileComponentType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Condition")
		int CurrentStrength;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Condition")
		FVector Origin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Condition")
		class APawn* HitPawn;

};
