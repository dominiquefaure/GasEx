// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/AbilitySystem/GasExGameplayAbilityParameters.h"
#include "BaseAttackAbilityParameters.generated.h"




/**
 *
 */
UCLASS()
class UBaseAttackAbilityParameters : public UGasExGameplayAbilityParameters
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontage;

	virtual void SetProperties( const UObject* InObject ) override;

};
