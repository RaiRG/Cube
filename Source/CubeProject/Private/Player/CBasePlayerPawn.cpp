// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CBasePlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Player/CBasePlayerController.h"
#include "Player/Components/CBaseMovementComponent.h"
#include "Player/Components/CExtendedMovementComponent.h"
#include "Player/DataAssets/CInputVelocityMapping_DataAsset.h"

ACBasePlayerPawn::ACBasePlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(StaticMeshComponent);

	MovementComponent = CreateDefaultSubobject<UCExtendedMovementComponent>("MovementComponent");
	MovementComponent->SetComponentForMovement(StaticMeshComponent);
}

void ACBasePlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACBasePlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBasePlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);

	if (auto* PlayerController = Cast<ACBasePlayerController>(GetController()))
	{
		auto InputData = PlayerController->GetInputDataAsset();
		check(InputData);
		
		for (auto InputAction : InputData->GetAllVelocityChangingInputActions())
		{
			float Velocity;
			if (InputData->TryGetVelocityForAction(InputAction, Velocity))
			{
				EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, MovementComponent,
				                                   &UCExtendedMovementComponent::OnChangeMovementVelocity, Velocity);
			}
		}

		EnhancedInputComponent->BindAction(InputData->GetManualMovementInputAction(), ETriggerEvent::Triggered,
		                                   MovementComponent, &UCExtendedMovementComponent::OnManualMovementInput);

		EnhancedInputComponent->BindAction(InputData->GetEnableManualMovementInputAction(), ETriggerEvent::Started,
		                                   MovementComponent, &UCExtendedMovementComponent::EnableAutoPilot);
	}
}
