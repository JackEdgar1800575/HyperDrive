// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HyperDrivePawn.h"
#include "PickupActor.generated.h"

//Enum for identifying the type of pickup that


UCLASS(Blueprintable)
class HYPERDRIVE_API APickupActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMeshComponent;

	UPROPERTY(Category = "Audio", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USoundBase* PickupSound;
	//UPROPERTY(Category = "WWise", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//	class UAkAudioEvent* PickupEvent;
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PickupResponse(AHyperDrivePawn* Player);

	void PlayPickupSound();

};
