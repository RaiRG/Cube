// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/CExtendedMovementComponent.h"

#include "InputActionValue.h"


UCExtendedMovementComponent::UCExtendedMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCExtendedMovementComponent::EnableAutoPilot()
{
	SetEnableAutoPilot(!bAutoPilotEnabled);
}

void UCExtendedMovementComponent::OnManualMovementInput(const FInputActionValue& InputActionValue)
{	
	if (InputActionValue[0] > 0)
	{
		MoveManual(true);
	}
	else
	{
		MoveManual(false);
	}
}

void UCExtendedMovementComponent::OnChangeMovementVelocity(float NewVelocity)
{
	ChangeVelocity(NewVelocity);
}
