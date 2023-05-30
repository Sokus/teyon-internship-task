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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USceneComponent*> TireEmitters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	class USceneComponent *TireEmitterBackLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	class USceneComponent *TireEmitterBackRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	class UNiagaraSystem* TireNiagaraSysytem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX|Variable Names")
	FName SmokeSpawnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX|Variable Names")
	FName SkidMarkOpacity;


private:
	TArray<class UNiagaraComponent*> TireNiagaraComponents;
	float TireEffectsCooldown;

protected:
	virtual void BeginPlay() override;

public:
	void AccelerationProc(const FInputActionValue& Value);
	void SteeringProc(const FInputActionValue& Value);
	void BrakeProc(const FInputActionValue& Value);
	void HandbrakeProc(const FInputActionValue& Value);

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	virtual void Tick(float DeltaTime) override;

private:

	void TireEffects();
};
