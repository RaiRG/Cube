// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CBasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/Components/CExtendedMovementComponent.h"
#include "Player/DataAssets/CInputVelocityMapping_DataAsset.h"

void ACBasePlayerController::BeginPlay()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ACBasePlayerController::OnTryToManualMovementInput(const FInputActionValue& InputActionValue)
{
	if (!GetPawn())
	{
		return;
	}
	if (auto MovementComponent = GetPawn()->GetComponentByClass<UCBaseMovementComponent>())
	{
		auto const bChangeDirectionOfMovement = !MovementComponent->GetIsAutoPilotEnabled() &&
		(InputActionValue[0] > 0 && !MovementComponent->GetIsMovingForward() ||
			InputActionValue[0] < 0 && MovementComponent->GetIsMovingForward());

		auto const bFirstManualMovementInput = !MovementComponent->GetIsAutoPilotEnabled() && !bStartMovementOnManual;
		
		const auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			GetLocalPlayer());

		if (InputSubsystem && (bChangeDirectionOfMovement || bFirstManualMovementInput))
		{
			bStartMovementOnManual = true;
			auto Keys = InputSubsystem->QueryKeysMappedToAction(GetInputDataAsset()->GetManualMovementInputAction());
			for (auto Key : Keys)
			{
				if (IsInputKeyDown(Key))
				{
					OnPrintInfoAboutManualMovement(InputActionValue[0], Key.GetDisplayName());
				}
			}
		}
	}
}

void ACBasePlayerController::SetKeyMapping(const UInputMappingContext* KeyMapping) const
{
	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(InputDataAsset->GetDefaultPlayerMappingContext(), 0);
	}
}

void ACBasePlayerController::OnEnableAutoPilot()
{
	if (!GetPawn())
	{
		return;
	}
	if (auto MovementComponent = GetPawn()->GetComponentByClass<UCBaseMovementComponent>())
	{
		if (!MovementComponent->GetIsAutoPilotEnabled())
		{
			bStartMovementOnManual = false;
		}
	}
}

void ACBasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(GetInputDataAsset());
	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);

	SetKeyMapping(GetInputDataAsset()->GetDefaultPlayerMappingContext());

	EnhancedInputComponent->BindAction(GetInputDataAsset()->GetManualMovementInputAction(), ETriggerEvent::Triggered,
	                                   this, &ACBasePlayerController::OnTryToManualMovementInput);

	EnhancedInputComponent->BindAction(GetInputDataAsset()->GetEnableManualMovementInputAction(), ETriggerEvent::Started,
										   this, &ACBasePlayerController::OnEnableAutoPilot);
}
