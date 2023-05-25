// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PraktykiGameModeBase.generated.h"

/**
 *
 */
USTRUCT()
struct FZoneInteractionInfo
{
	GENERATED_BODY()

	bool bWasVisited;
	float Time;
	float LastTime;
};

/**
 *
 */
UCLASS()
class PRAKTYKI_API APraktykiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APraktykiGameModeBase();

	UFUNCTION(BlueprintCallable)
	float GetTime() { return Time; }

	void OnWentOffTrack(void);
	void OnZoneOverlap(AActor *Zone);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPraktykiUserWidget *PraktykiUserWidget;

protected:
	int Laps;
	float Time;
	float LastTime;
	float BestTime;
	bool bCutDetected;

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason);
	virtual void Tick(float DeltaTime) override;


private:
	TArray<AActor*> ZoneActors;
	TArray<FZoneInteractionInfo> ZoneInteractionInfos;

};
