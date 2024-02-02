// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GasExGameplayAbilityParameters.generated.h"




/**
 *
 */
UCLASS( Blueprintable)
class GASEX_API UGasExGameplayAbilityParameters : public UObject
{
	GENERATED_BODY()

public:

	virtual void SetProperties( const UObject* InObject ) {}
};
