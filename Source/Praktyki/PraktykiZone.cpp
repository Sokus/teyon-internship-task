// Copyright 2023 Teyon. All Rights Reserved.


#include "PraktykiZone.h"
#include "PraktykiGameModeBase.h"
#include "PraktykiWheeledVehiclePawn.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APraktykiZone::APraktykiZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APraktykiZone::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APraktykiZone::OnActorOverlap);
}

// Called every frame
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

