// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbility.h"
#include "GxActionNode_Base.generated.h"


struct FGxActionContext;

/**
 * 
 */
UCLASS()
class GXACTIONS_API UGxActionNode_Base : public UObject
{
	GENERATED_BODY()

public:


	/*
	* List of possible actions that can start from this one
	*/
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TArray<TObjectPtr<UGxActionNode_Base>> LinkedActions;


	virtual bool TryExecute( FGxActionContext& InContext , FGameplayTag InInputTag );

	virtual bool TryExecuteNextAction( FGxActionContext& InContext , FGameplayTag InInputTag , TObjectPtr<UGxActionNode_Base>& OutActionNode );
};
