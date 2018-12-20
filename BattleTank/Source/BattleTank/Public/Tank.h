﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent *TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent *TankMovementComponent = nullptr;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel *BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret *TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 10000;	// cm/s
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float ReloadTimeInSeconds = 3.0f;

	UTankBarrel *Barrel = nullptr;
	float LastFireTime = 0.0f;
};
