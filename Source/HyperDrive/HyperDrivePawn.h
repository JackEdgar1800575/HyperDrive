// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Character.h"
#include "HyperDrivePawn.generated.h"

UCLASS(Blueprintable)
class AHyperDrivePawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AHyperDrivePawn();

	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/* The speed our ship moves around the level */
	UPROPERTY(Category = "Gameplay | Player Stats", EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	UPROPERTY(Category = "Gameplay | Player Stats", EditAnywhere, BlueprintReadWrite)
		int MaxHealth;

	UPROPERTY(Category = "Gameplay | Player Stats", EditAnywhere, BlueprintReadWrite)
		int MaxArmour;

	UPROPERTY(Category = "Gameplay | Current State", VisibleAnywhere, BlueprintReadWrite)
		int CurrentHealth;

	UPROPERTY(Category = "Gameplay | Current State", VisibleAnywhere, BlueprintReadWrite)
		int CurrentArmour;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		class AWeaponActor* CurrentWeapon;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		TArray<AWeaponActor*> WeaponInventory;

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	//////////////////
	//Player Actions//
	//////////////////
	/* Fire in front of the player */
	void Fire();

	//Input
	void ActivateWeaponFiring();
	void DeactivateWeaponFiring();

	bool bIsFiring;

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;
};

