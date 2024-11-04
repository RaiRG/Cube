// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CBasePlayerPawn.generated.h"

class UArrowComponent;
class UCameraComponent;
class UCExtendedMovementComponent;
class UCInputVelocityMapping_DataAsset;
UCLASS()
class CUBEPROJECT_API ACBasePlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ACBasePlayerPawn();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	USceneComponent*			RootSceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	UCExtendedMovementComponent*	MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	UStaticMeshComponent*		StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	UArrowComponent*			ArrowComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	UCameraComponent*			CameraComponent;
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
};
