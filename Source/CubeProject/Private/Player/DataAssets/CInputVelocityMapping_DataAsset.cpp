// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DataAssets/CInputVelocityMapping_DataAsset.h"

TArray<UInputAction*> UCInputVelocityMapping_DataAsset::GetAllVelocityChangingInputActions() const
{
	TArray<UInputAction*> InputActions;
	ChangeVelocityByInputMapping.GetKeys(InputActions);
	return InputActions;
}

bool UCInputVelocityMapping_DataAsset::TryGetVelocityForAction(const UInputAction* InputAction, float& Result) const
{
	if(ChangeVelocityByInputMapping.Contains(InputAction))
	{
		Result = ChangeVelocityByInputMapping[InputAction];
		return true;
	}
	return false;
}
