// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PraktykiTrackGrass.generated.h"

UCLASS()
class PRAKTYKI_API APraktykiTrackGrass : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APraktykiTrackGrass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
