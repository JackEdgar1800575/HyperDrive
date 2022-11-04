// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DestructableActor.generated.h"

UCLASS(Blueprintable)
class HYPERDRIVE_API ADestructableActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent;
	
public:	
	// Sets default values for this actor's properties
	ADestructableActor();

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return MeshComponent; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void TakeDamage(int InDmg);

	UFUNCTION(BlueprintCallable)
		void OnDestroy();

	//Object Properties
	UPROPERTY(Category = "Destructible | Stats", EditAnywhere, BlueprintReadWrite)
		int DefaultHealth;
	UPROPERTY(Category = "Destructible | Stats", EditAnywhere, BlueprintReadOnly)
		int CurrentHealth;
	UPROPERTY(Category = "Destructible | Audio", EditAnywhere, BlueprintReadWrite)
		class USoundBase* DestroySound;


};
