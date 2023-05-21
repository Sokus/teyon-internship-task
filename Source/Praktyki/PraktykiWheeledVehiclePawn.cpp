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
    UE_LOG(LogTemp, Warning, TEXT("AccelerationProc"));
}

void APraktykiWheeledVehiclePawn::SteeringProc(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("SteeringProc"));
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
}

void APraktykiWheeledVehiclePawn::Tick(float DeltaTime)
{
    //this->GetVehicleMovementComponent()->SetThrottleInput(0.1f);
}