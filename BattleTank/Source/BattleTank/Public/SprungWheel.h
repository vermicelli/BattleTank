﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

private:
	void SetupComponent();
	void ApplyForce();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent *Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent *Axle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		UPhysicsConstraintComponent *MassWheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		UPhysicsConstraintComponent *AxleWheelConstraint = nullptr;

	float TotalForceMagnitudeThisFrame = 0.0f;
};
