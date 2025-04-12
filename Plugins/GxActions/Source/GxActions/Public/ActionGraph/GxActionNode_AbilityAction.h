// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbility.h"
#include "GxActionNode_Base.h"
#include "GxActionNode_AbilityAction.generated.h"



/**
 *
 */
UCLASS()
class GXACTIONS_API UGxActionNode_AbilityAction : public UGxActionNode_Base
{
	GENERATED_BODY()

public:

	/*
	* The Gameplay tag that identify The required input
	*/ 
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag InputTag;

	/*
	* The Gameplay tag that identify The ability to use
	*/
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag AbilityTag;


	virtual bool TryExecute( FGxActionContext& InContext , FGameplayTag InInputTag ) override;

};
