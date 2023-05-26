// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PraktykiUserWidget.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API UPraktykiUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBestTime(float NewBestTime);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateLastTime(float NewLastTime, bool bCutDetected);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateLaps(int Laps, int MaxLaps);
};
