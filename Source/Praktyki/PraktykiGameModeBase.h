// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PraktykiGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API APraktykiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void OnWentOffTrack(void);
	void OnZoneOverlap(AActor *Zone);

protected:
	virtual void BeginPlay() override;

private:
	TArray<AActor*> ZoneActors;
};
