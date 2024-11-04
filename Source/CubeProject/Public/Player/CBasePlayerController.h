// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "CBasePlayerController.generated.h"

class UCInputVelocityMapping_DataAsset;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class CUBEPROJECT_API ACBasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	UCInputVelocityMapping_DataAsset* GetInputDataAsset() const {return InputDataAsset; }
	
protected:		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	UCInputVelocityMapping_DataAsset* InputDataAsset;
	
	bool bStartMovementOnManual;

	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	void SetKeyMapping(const UInputMappingContext* KeyMapping) const;

	UFUNCTION()
	void OnEnableAutoPilot();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnPrintInfoAboutManualMovement(float Scale, const FText& Key);
	
	UFUNCTION()
	void OnTryToManualMovementInput(const FInputActionValue& InputActionValue);
};
