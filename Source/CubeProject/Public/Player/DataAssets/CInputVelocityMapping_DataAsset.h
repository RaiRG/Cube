// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CInputVelocityMapping_DataAsset.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class CUBEPROJECT_API UCInputVelocityMapping_DataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputMappingContext*					DefaultPlayerMappingContext;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<UInputAction*, float>					ChangeVelocityByInputMapping;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputAction*					ManualMovementInputsAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputAction*					EnableManualMovementInputAction;
	
public:
	UFUNCTION(BlueprintPure)
	TArray<UInputAction*> GetAllVelocityChangingInputActions() const;

	UFUNCTION(BlueprintPure)
	UInputAction* GetManualMovementInputAction() const { return ManualMovementInputsAction; };
	
	UFUNCTION(BlueprintPure)
	UInputAction* GetEnableManualMovementInputAction() const { return EnableManualMovementInputAction; }; 
	
	UFUNCTION(BlueprintPure)
	UInputMappingContext* GetDefaultPlayerMappingContext() const { return DefaultPlayerMappingContext; };
	
	UFUNCTION(BlueprintPure)
	bool TryGetVelocityForAction(const UInputAction* InputAction, float& Result) const;
};
