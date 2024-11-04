// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBaseMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CUBEPROJECT_API UCBaseMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCBaseMovementComponent();

	UFUNCTION(BlueprintCallable, Category="Movement|Setup")
	void SetComponentForMovement(USceneComponent* InMovementComponent);

	UFUNCTION(BlueprintCallable, Category="Movement")
	void SetEnableAutoPilot(bool bInAutoPilotEnabled);

	UFUNCTION(BlueprintCallable, Category="Movement")
	void MoveManual(bool bInIsMovingForward);

	UFUNCTION(BlueprintPure, Category="Movement")
	bool GetIsMovingForward() const { return bIsMovingForward; }
	
	UFUNCTION(BlueprintPure, Category="Movement")
	bool GetIsAutoPilotEnabled() const {return bAutoPilotEnabled; }
protected:
	virtual void BeginPlay() override;
	FVector GetCurrentDirection() const;
	bool CanMoveOnLocation(const FVector& NewLocation) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement|Settings")
	float DefaultVelocity = 100.0f;

#pragma region RUNTIME
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement|Runtime")
	float CurrentVelocity = 0.0f;

	UPROPERTY()
	USceneComponent* ComponentForMovement = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement|Runtime")
	bool bIsMovingForward = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement|Runtime")
	FVector BackBound = FVector::ZeroVector;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement|Runtime")
	FVector FrontBound = FVector::ZeroVector;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement|Runtime")
	bool bAutoPilotEnabled = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement|Runtime")
	bool bNeedMoveOnNextTick = false;

#pragma endregion RUNTIME
	
	

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void ChangeVelocity(float NewVelocity);

	
};
