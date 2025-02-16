// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "Attacks/GxAttackMoveSet.h"
#include "GxAbilitySystemComponent.h"
#include "Abilities/GxGameplayAbility.h"

//-----------------------------------------------------------------------------------------
void UGxAttackMoveSet::Register( FString InName , UDataTable* InTable , UGxAbilitySystemComponent* InASC )
{
	if( InASC == nullptr )
	{
		return;
	}

	if( InTable == nullptr )
	{
		return;
	}

	Name								=	InName;


	for( auto It : InTable->GetRowMap() )
	{
		UGxAttackAction* NewAttack			=	NewObject<UGxAttackAction>();
		FAttackDefinition* Definition		=	(FAttackDefinition*)It.Value;

		NewAttack->AbilityTag				=	Definition->AbilityTag;
		NewAttack->Ability					=	Definition->Ability;
		NewAttack->NextAttacks				=	Definition->NextAttacks;

		if( Definition->Ability != nullptr )
		{
			NewAttack->AbilitySpec			=	InASC->BuildAbilitySpecFromClass( Definition->Ability , 0 , -1 );
			InASC->GiveAbility( NewAttack->AbilitySpec );
		}

		AttackMoves.Add( NewAttack );
	}

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
TObjectPtr<UGxAttackAction> UGxAttackMoveSet::GetCombatAttack( FGameplayTag InTag )
{
	for( UGxAttackAction* Attack : AttackMoves )
	{
		if( Attack->AbilityTag == InTag )
		{
			return Attack;
		}
	}
	return nullptr;
}
//-----------------------------------------------------------------------------------------
