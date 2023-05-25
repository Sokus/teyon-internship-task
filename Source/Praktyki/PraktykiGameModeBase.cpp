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

void APraktykiGameModeBase::OnWentOffTrack(void)
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Went off-track")));
    bCutDetected = true;
}



void APraktykiGameModeBase::OnZoneOverlap(AActor *Zone)
{
    for (int32 ZoneIndex = 0; ZoneIndex < ZoneActors.Num(); ZoneIndex += 1)
    {
        if (ZoneActors[ZoneIndex] != Zone) continue;

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
                            PraktykiUserWidget->UpdateBestTime(BestTime);
                        }

                        LastTime = Time;
                        PraktykiUserWidget->UpdateLastTime(LastTime, bCutDetected);

                        for (int32 ClearZoneIndex = 0; ClearZoneIndex < ZoneActors.Num(); ClearZoneIndex += 1)
                        {
                            ZoneInteractionInfos[ClearZoneIndex].bWasVisited = false;
                        }
                        bCutDetected = false;
                        Time = 0.0f;
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

    Laps = 0;
    Time = LastTime = BestTime = 0.0f;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APraktykiZone::StaticClass(), ZoneActors);

    ZoneInteractionInfos.Init({}, ZoneActors.Num());

    UGameInstance *GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
    if (UPraktykiGameInstance *PraktykiGameInstance = Cast<UPraktykiGameInstance>(GameInstance))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Lap limit: %d"), PraktykiGameInstance->LapLimit);
    }
}

void APraktykiGameModeBase::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    ZoneInteractionInfos.Empty();
}

void APraktykiGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Time += DeltaTime;
}
