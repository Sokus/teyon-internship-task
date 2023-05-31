// Copyright 2023 Teyon. All Rights Reserved.


#include "PraktykiZone.h"
#include "PraktykiGameModeBase.h"
#include "PraktykiWheeledVehiclePawn.h"

#include "Kismet/GameplayStatics.h"

APraktykiZone::APraktykiZone()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APraktykiZone::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APraktykiZone::OnActorOverlap);
}

void APraktykiZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APraktykiZone::OnActorOverlap(AActor *OverlappedActor, AActor *OtherActor)
{
    if ((OtherActor != nullptr) && (OtherActor != this))
    {
		if (APraktykiWheeledVehiclePawn *WheeledVehiclePawn = Cast<APraktykiWheeledVehiclePawn>(OtherActor))
		{
            AGameModeBase *GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
            if (APraktykiGameModeBase *PraktykiGameModeBase = Cast<APraktykiGameModeBase>(GameModeBase))
            {
                PraktykiGameModeBase->OnZoneOverlap(OverlappedActor);
            }
		}
	}
}

