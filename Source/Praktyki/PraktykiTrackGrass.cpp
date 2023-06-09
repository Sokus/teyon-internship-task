// Copyright 2023 Teyon. All Rights Reserved.


#include "PraktykiTrackGrass.h"
#include "PraktykiGameModeBase.h"
#include "PraktykiWheeledVehiclePawn.h"

#include "Kismet/GameplayStatics.h"

APraktykiTrackGrass::APraktykiTrackGrass()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APraktykiTrackGrass::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APraktykiTrackGrass::OnActorOverlap);
}

void APraktykiTrackGrass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APraktykiTrackGrass::OnActorOverlap(AActor *OverlappedActor, AActor *OtherActor)
{
    if ((OtherActor != nullptr) && (OtherActor != this))
    {
		if (APraktykiWheeledVehiclePawn *WheeledVehiclePawn = Cast<APraktykiWheeledVehiclePawn>(OtherActor))
		{
            AGameModeBase *GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
            if (APraktykiGameModeBase *PraktykiGameModeBase = Cast<APraktykiGameModeBase>(GameModeBase))
            {
                PraktykiGameModeBase->OnWentOffTrack();
            }
		}
	}
}