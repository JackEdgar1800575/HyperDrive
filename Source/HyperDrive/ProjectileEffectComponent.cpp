// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileEffectComponent.h"

// Sets default values for this component's properties
UProjectileEffectComponent::UProjectileEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectileEffectComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UProjectileEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectileEffectComponent::ActivateHitEffect()
{
}

