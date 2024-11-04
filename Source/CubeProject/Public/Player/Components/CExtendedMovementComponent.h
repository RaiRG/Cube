// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBaseMovementComponent.h"
#include "CExtendedMovementComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInput, const FInputActionValue&, InputActionValue);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CUBEPROJECT_API UCExtendedMovementComponent : public UCBaseMovementComponent
{
	GENERATED_BODY()
	
public:
	UCExtendedMovementComponent();
	
	UFUNCTION()
	void EnableAutoPilot();
	
	UFUNCTION()
	void OnManualMovementInput(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void OnChangeMovementVelocity(float NewVelocity);

	UPROPERTY(BlueprintAssignable, Category="Movement")
	FOnPlayerInput OnTryToChangeMovementMode;

};
