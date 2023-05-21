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

public:
	void AccelerationProc(const FInputActionValue& Value);
	void SteeringProc(const FInputActionValue& Value);


	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	void Tick(float DeltaTime);
};
