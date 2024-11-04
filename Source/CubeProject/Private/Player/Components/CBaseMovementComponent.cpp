// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/CBaseMovementComponent.h"

#include "Kismet/GameplayStatics.h"


UCBaseMovementComponent::UCBaseMovementComponent(): ComponentForMovement(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCBaseMovementComponent::SetComponentForMovement(USceneComponent* InMovementComponent)
{
	ComponentForMovement = InMovementComponent;
}

void UCBaseMovementComponent::SetEnableAutoPilot(bool bInAutoPilotEnabled)
{
	bAutoPilotEnabled = bInAutoPilotEnabled;
}

void UCBaseMovementComponent::MoveManual(bool bInIsMovingForward)
{
	if (!bAutoPilotEnabled)
	{
		bIsMovingForward = bInIsMovingForward;
		bNeedMoveOnNextTick = true;
	}
}

void UCBaseMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentVelocity = DefaultVelocity;

	check(ComponentForMovement);
}

FVector UCBaseMovementComponent::GetCurrentDirection() const
{
	return bIsMovingForward
		       ? ComponentForMovement->GetForwardVector()
		       : -1 * ComponentForMovement->GetForwardVector();
}

bool UCBaseMovementComponent::CanMoveOnLocation(const FVector& NewLocation) const
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		int ScreenSizeX;
		int ScreenSizeY;
		PlayerController->GetViewportSize(ScreenSizeX, ScreenSizeY);

		FVector2D ScreenLocation;
		PlayerController->ProjectWorldLocationToScreen(NewLocation, ScreenLocation);

		if (ScreenLocation.X >= ScreenSizeX || ScreenLocation.Y >= ScreenSizeY || ScreenLocation.X <= 0 ||
			ScreenLocation.Y <= 0)
		{
			return false;
		}

		return true;
	}
	return false;
}


void UCBaseMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (bAutoPilotEnabled || !bAutoPilotEnabled && bNeedMoveOnNextTick)
	{
		const auto Direction = GetCurrentDirection();

		FVector NewLocation = ComponentForMovement->GetComponentLocation() + (Direction * CurrentVelocity *
			DeltaTime);

		if (CanMoveOnLocation(NewLocation))
		{
			ComponentForMovement->SetWorldLocation(NewLocation);
		}
		else
		{
			if (bAutoPilotEnabled)
			{
				bIsMovingForward = !bIsMovingForward;
			}
		}
		bNeedMoveOnNextTick = false;
	}
}

void UCBaseMovementComponent::ChangeVelocity(float NewVelocity)
{
	CurrentVelocity = NewVelocity;
}
