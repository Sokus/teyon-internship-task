// Copyright 2023 Teyon. All Rights Reserved.


#include "PraktykiWheeledVehiclePawn.h"
#include "PraktykiInputDataAsset.h"

#include "WheeledVehiclePawn.h"
#include "ChaosVehicleMovementComponent.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"

void APraktykiWheeledVehiclePawn::AccelerationProc(const FInputActionValue& Value)
{
    const float AccelerationValue = Value.Get<float>();
    GetVehicleMovementComponent()->SetThrottleInput(AccelerationValue);
}

void APraktykiWheeledVehiclePawn::SteeringProc(const FInputActionValue& Value)
{
    const float SteeringValue = Value.Get<float>();
    GetVehicleMovementComponent()->SetSteeringInput(SteeringValue);
}

void APraktykiWheeledVehiclePawn::BrakeProc(const FInputActionValue& Value)
{
    const float BrakeValue = Value.Get<float>();
    GetVehicleMovementComponent()->SetBrakeInput(BrakeValue);
}

void APraktykiWheeledVehiclePawn::HandbrakeProc(const FInputActionValue& Value)
{
    const bool HandbrakeValue = Value.Get<bool>();
    GetVehicleMovementComponent()->SetHandbrakeInput(HandbrakeValue);
}

void APraktykiWheeledVehiclePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    EnhancedInputComponent->BindAction(InputDataAsset->InputAccelerate, ETriggerEvent::Triggered, this, &APraktykiWheeledVehiclePawn::AccelerationProc);
    EnhancedInputComponent->BindAction(InputDataAsset->InputSteering, ETriggerEvent::Triggered, this, &APraktykiWheeledVehiclePawn::SteeringProc);
    EnhancedInputComponent->BindAction(InputDataAsset->InputBrake, ETriggerEvent::Triggered, this, &APraktykiWheeledVehiclePawn::BrakeProc);
    EnhancedInputComponent->BindAction(InputDataAsset->InputHandbrake, ETriggerEvent::Triggered, this, &APraktykiWheeledVehiclePawn::HandbrakeProc);
}

void APraktykiWheeledVehiclePawn::Tick(float DeltaTime)
{
    //this->GetVehicleMovementComponent()->SetThrottleInput(0.1f);
}