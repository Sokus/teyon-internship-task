// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "InputMappingContext.h"
#include "PraktykiInputDataAsset.h"
#include "InputActionValue.h"
#include "PraktykiWheeledVehiclePawn.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API APraktykiWheeledVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UPraktykiInputDataAsset* InputDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Engine Sound")
	float IdleRPM;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Engine Sound")
	float MaxRPM;

	UPROPERTY(BlueprintReadOnly)
	float RevPercent = 0.0f;

	UFUNCTION(BlueprintCallable)
	void Overlap(AActor* Other);

public:
	void AccelerationProc(const FInputActionValue& Value);
	void SteeringProc(const FInputActionValue& Value);
	void BrakeProc(const FInputActionValue& Value);
	void HandbrakeProc(const FInputActionValue& Value);

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	virtual void Tick(float DeltaTime) override;
};
