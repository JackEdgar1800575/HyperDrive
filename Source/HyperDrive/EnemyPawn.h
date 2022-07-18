// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

UCLASS(Blueprintable)
class HYPERDRIVE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent;

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

	FORCEINLINE class UStaticMeshComponent* GetEnemyMesh() const { return MeshComponent; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UFUNCTION(BlueprintCallable)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void DamageEnemy(int InDmg,bool IsArmourPiercing = false);

	UFUNCTION(BlueprintCallable)
		virtual void OnDestroyEnemy();

	//Enemy Properties
	UPROPERTY(Category = "Enemy | Stats", EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	UPROPERTY(Category = "Enemy | Stats", EditAnywhere, BlueprintReadWrite)
		int MaxHealth;

	UPROPERTY(Category = "Enemy | Stats", EditAnywhere, BlueprintReadWrite)
		int MaxArmour;

	UPROPERTY(Category = "Enemy | Current State", VisibleAnywhere, BlueprintReadWrite)
		int CurrentHealth;

	UPROPERTY(Category = "Enemy | Current State", VisibleAnywhere, BlueprintReadWrite)
		int CurrentArmour;

	/*UPROPERTY(Category = "WWise", VisibleAnywhere, BlueprintReadWrite)
	class UAkAudioEvent* DeathSoundEvent;*/


};
