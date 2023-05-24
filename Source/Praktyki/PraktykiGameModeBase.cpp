// Fill out your copyright notice in the Description page of Project Settings.


#include "PraktykiGameModeBase.h"
#include "PraktykiZone.h"

#include "Kismet/GameplayStatics.h"

void APraktykiGameModeBase::OnWentOffTrack(void)
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Went off-track")));
}

void APraktykiGameModeBase::OnZoneOverlap(AActor *Zone)
{
    for (int32 ZoneIndex = 0; ZoneIndex < ZoneActors.Num(); ZoneIndex += 1)
    {
        if (Zone == ZoneActors[ZoneIndex])
        {
            UE_LOG(LogTemp, Warning, TEXT("%d"), ZoneIndex);
        }
    }
}

void APraktykiGameModeBase::BeginPlay()
{
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APraktykiZone::StaticClass(), ZoneActors);
}