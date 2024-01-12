// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "GasExGameplayAbility.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam( FGasExAbilityEnded , bool Canceled );


/**
 * 
 */
UCLASS()
class GASEX_API UGasExGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGasExGameplayAbility( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );

};
