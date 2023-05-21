// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "PraktykiInputDataAsset.generated.h"


/**
 *
 */
UCLASS()
class PRAKTYKI_API UPraktykiInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	UInputAction *InputAccelerate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	UInputAction *InputSteering;
};
