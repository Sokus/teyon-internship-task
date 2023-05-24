// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PraktykiZone.generated.h"

UENUM()
enum class EPraktykiZoneType : uint8
{
	StartFinish,
	Checkpoint,
};

UCLASS()
class PRAKTYKI_API APraktykiZone : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPraktykiZoneType Type;

	APraktykiZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnActorOverlap(AActor *OverlappedActor, AActor *OtherActor);
};
