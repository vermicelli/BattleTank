// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::SetPawn(APawn *InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }
		
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!PlayerTank || !ControlledTank) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
