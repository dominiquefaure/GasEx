// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Abilities/GameplayAbility.h"


#include "GasExActionNodeBase.generated.h"


class UGasExActionNodeLink;


/**
 * 
 */
UCLASS()
class GASEX_API UGasExActionNodeBase : public UObject
{
	GENERATED_BODY()

public:


	// Actions that can Launch from the current one
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TArray<UGasExActionNodeBase*> NextActions;

};
