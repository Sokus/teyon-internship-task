// Fill out your copyright notice in the Description page of Project Settings.


#include "PraktykiGameModeBase.h"
#include "PraktykiZone.h"
#include "PraktykiGameInstance.h"
#include "PraktykiUserWidget.h"

#include "Kismet/GameplayStatics.h"

APraktykiGameModeBase::APraktykiGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APraktykiGameModeBase::UpdateSpeed(float Speed)
{
    if (PraktykiUserWidget)
    {
        PraktykiUserWidget->UpdateSpeed(Speed);
    }
}

void APraktykiGameModeBase::OnWentOffTrack(void)
{
    bCutDetected = true;
}

void APraktykiGameModeBase::OnZoneOverlap(AActor *Zone)
{
    for (int32 ZoneIndex = 0; ZoneIndex < ZoneActors.Num(); ZoneIndex += 1)
    {
        if (ZoneActors[ZoneIndex] != Zone) continue;


        ZoneInteractionInfos[ZoneIndex].Time = Time;
        if (ZoneInteractionInfos[ZoneIndex].LastTime != 0.0f)
        {
            float TimeDelta = ZoneInteractionInfos[ZoneIndex].Time - ZoneInteractionInfos[ZoneIndex].LastTime;
            if (PraktykiUserWidget)
            {
                PraktykiUserWidget->UpdateTimeDelta(TimeDelta);
            }
        }

        if (APraktykiZone *PraktykiZone = Cast<APraktykiZone>(Zone))
        {
            switch (PraktykiZone->Type)
            {
                case EPraktykiZoneType::StartFinish:
                {


                    if (ZoneInteractionInfos[ZoneIndex].bWasVisited)
                    {
                        if (!bCutDetected)
                        {
                            for (int32 CheckZoneIndex = 0; CheckZoneIndex < ZoneActors.Num(); CheckZoneIndex += 1)
                            {
                                if (ZoneInteractionInfos[CheckZoneIndex].bWasVisited == false)
                                {
                                    bCutDetected = true;
                                    break;
                                }
                            }
                        }

                        if ((bCutDetected == false) && (BestTime == 0.0f || BestTime > Time))
                        {
                            BestTime = Time;

                            if (PraktykiUserWidget)
                            {
                                PraktykiUserWidget->UpdateBestTime(BestTime);
                            }
                        }

                        LastTime = Time;

                        if (LapLimit > 0 && Laps == LapLimit)
                        {
                            GameFinished();
                        }
                        else
                        {
                            Laps += 1;
                        }

                        if (PraktykiUserWidget)
                        {
                            PraktykiUserWidget->UpdateLastTime(LastTime, bCutDetected);
                            PraktykiUserWidget->UpdateLaps(Laps, LapLimit);
                        }

                        for (int32 ClearZoneIndex = 0; ClearZoneIndex < ZoneActors.Num(); ClearZoneIndex += 1)
                        {
                            ZoneInteractionInfos[ClearZoneIndex].bWasVisited = false;
                            ZoneInteractionInfos[ClearZoneIndex].LastTime = ZoneInteractionInfos[ClearZoneIndex].Time;
                        }
                        bCutDetected = false;
                        Time = 0.0f;
                    }
                    else
                    {
                        bLapsStarted = true;
                    }

                    ZoneInteractionInfos[ZoneIndex].bWasVisited = true;
                } break;

                case EPraktykiZoneType::Checkpoint:
                {
                    ZoneInteractionInfos[ZoneIndex].bWasVisited = true;
                } break;

                default: break;
            }
        }
    }
}

void APraktykiGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    Laps = 1;
    Time = LastTime = BestTime = 0.0f;
    bCutDetected = bLapsStarted = false;
    LapLimit = 0;


    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APraktykiZone::StaticClass(), ZoneActors);

    ZoneInteractionInfos.Init({}, ZoneActors.Num());

    UGameInstance *GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
    if (UPraktykiGameInstance *PraktykiGameInstance = Cast<UPraktykiGameInstance>(GameInstance))
    {
        TimeLeft = PraktykiGameInstance->TimeLimit;
        LapLimit = PraktykiGameInstance->LapLimit;
    }
    if (PraktykiUserWidget)
    {
        PraktykiUserWidget->UpdateLaps(Laps, LapLimit);
    }
}

void APraktykiGameModeBase::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    ZoneInteractionInfos.Empty();
}

void APraktykiGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bLapsStarted)
    {
        Time += DeltaTime;

        if (TimeLeft > 0.0f && TimeLeft <= DeltaTime)
        {
            GameFinished();
        }

        TimeLeft -= DeltaTime;
        if (TimeLeft < 0.0f) TimeLeft = 0.0f;
    }
}
