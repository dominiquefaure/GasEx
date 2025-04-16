// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbility.h"
#include "GxActionInputBuffer.h"
#include "GxActionContext.generated.h"

class UGxAbilitySystemComponent;
class UGxActionNode_Base;

UENUM()
enum class EGxActionState : uint8
{
	NoAction		=	0 ,	// No action currently playing, graph is in waiting state
	ActionInProgres	=	1,	// an Action is currently in Progress
	ActionFinished	=	9, // the Current Action just finished will go back to NoAction if no NextAction can be launched
};


/**
 *
 */
USTRUCT()
struct GXACTIONS_API FGxActionContext
{
	GENERATED_BODY()

public:

	TObjectPtr<UGxAbilitySystemComponent>	AbilitySystemComponent;

	EGxActionState							CurrentState;

	FGameplayTag							CurrentActionTag;

	UPROPERTY()
	FGxActionInputBuffer					InputBuffer;


	bool ExecuteAction( FGameplayTag& InActionTag );

	void OnInputTriggered( FGameplayTag InputTag );


	const FGameplayTag GetInputTag( bool InConsume = true );
};
