// Copyright 2023 Teyon. All Rights Reserved.


#include "PraktykiWheeledVehiclePawn.h"
#include "PraktykiInputDataAsset.h"
#include "PraktykiTrackGrass.h"
#include "PraktykiGameModeBase.h"

#include "WheeledVehiclePawn.h"
#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Components/BoxComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Math/UnrealMathUtility.h"

void APraktykiWheeledVehiclePawn::BeginPlay()
{
    Super::BeginPlay();

    TireNiagaraComponents.Init(nullptr, 4);
    TireEffectsCooldown = 0.0f;
}

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

    float EngineRPM = GetVehicleMovementComponent()->PhysicsVehicleOutput()->EngineRPM;
    RevPercent = (EngineRPM - IdleRPM) / (MaxRPM - IdleRPM);

    if (TireEffectsCooldown <= 0.0f)
    {
        TireEffects();
        TireEffectsCooldown = 0.2f;
    }
    else
    {
        TireEffectsCooldown -= DeltaTime;
    }

    AGameModeBase *GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
    if (APraktykiGameModeBase *PraktykiGameModeBase = Cast<APraktykiGameModeBase>(GameModeBase))
    {
        float MPHToKPH = 1.609344f;
        float SpeedMPH = GetVehicleMovementComponent()->GetForwardSpeedMPH();
        PraktykiGameModeBase->UpdateSpeed(SpeedMPH * MPHToKPH);
    }

    Super::Tick(DeltaTime);
}

void APraktykiWheeledVehiclePawn::TireEffects()
{
    UChaosWheeledVehicleMovementComponent *WheeledVehicleMovementComponent = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
    if (WheeledVehicleMovementComponent == nullptr) return;

    for (int32 WheelIndex = 2;
         WheelIndex < WheeledVehicleMovementComponent->GetNumWheels() && WheelIndex <= 3;
         WheelIndex += 1)
    {
        const FWheelStatus& WheelStatus = WheeledVehicleMovementComponent->GetWheelState(WheelIndex);
        bool bIsDrifting = ((WheelStatus.bIsSkidding || WheelStatus.bIsSlipping) && WheelStatus.bInContact);
        if (bIsDrifting)
        {
            if (TireNiagaraComponents[WheelIndex] == nullptr)
            {
                USceneComponent *AttachToComponent = WheelIndex == 2 ? TireEmitterBackLeft : TireEmitterBackRight;
                TireNiagaraComponents[WheelIndex] = UNiagaraFunctionLibrary::SpawnSystemAttached(
                    TireNiagaraSysytem, AttachToComponent, FName(), FVector(), FRotator(), EAttachLocation::Type::KeepRelativeOffset, false
                );
            }

            if (TireNiagaraComponents[WheelIndex] != nullptr)
            {
                float SlipMagnitudeAbsRangeClamped = FMath::GetMappedRangeValueClamped(TRange<float>::TRange(600.0f, 1000.0f), TRange<float>::TRange(0.0f, 1.0f), FMath::Abs(WheelStatus.SlipMagnitude));
                float SkidMagnitudeAbsRangeClamped = FMath::GetMappedRangeValueClamped(TRange<float>::TRange(1000.0f, 1500.0f), TRange<float>::TRange(0.0f, 1.0f), FMath::Abs(WheelStatus.SkidMagnitude));
                float SkidMarkOpacityValue = FMath::Clamp(SlipMagnitudeAbsRangeClamped+SkidMagnitudeAbsRangeClamped, 0.0f, 1.0f);

                TireNiagaraComponents[WheelIndex]->SetFloatParameter(SmokeSpawnRate, FMath::Sign(FMath::Abs(WheelStatus.SlipMagnitude)));
                TireNiagaraComponents[WheelIndex]->SetFloatParameter(SkidMarkOpacity, SkidMarkOpacityValue);
            }
        }
        else
        {
            if (TireNiagaraComponents[WheelIndex] != nullptr)
            {
                TireNiagaraComponents[WheelIndex]->SetFloatParameter(SmokeSpawnRate, 0.0f);
                TireNiagaraComponents[WheelIndex]->SetFloatParameter(SkidMarkOpacity, 0.0f);
                FDetachmentTransformRules DetachmentTransformRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, true);
                TireNiagaraComponents[WheelIndex]->DetachFromComponent(DetachmentTransformRules);
                TireNiagaraComponents[WheelIndex] = nullptr;
            }
        }
    }
}