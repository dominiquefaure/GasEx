// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GxAttackAction.h"

#include "GxAttackMoveSet.generated.h"

class UGxAttackAction;
class UGxAbilitySystemComponent;


/**
 *
 */
UCLASS( Blueprintable )
class GXCOMBAT_API UGxAttackMoveSet : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY( EditDefaultsOnly )
	FString Name;

	UPROPERTY( EditDefaultsOnly )
	TArray<TObjectPtr<UGxAttackAction>> AttackMoves;


	void Register( FString InName , UDataTable* InTable , UGxAbilitySystemComponent* InASC );


	TObjectPtr<UGxAttackAction> GetCombatAttack( FGameplayTag InTag );

};