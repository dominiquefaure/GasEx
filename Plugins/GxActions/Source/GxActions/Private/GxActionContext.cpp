// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "GxActionContext.h"
#include "ActionGraph/GxActionNode_Base.h"
#include "GxAbilitySystemComponent.h"

//---------------------------------------------------------------------------------------------
bool FGxActionContext::ExecuteAction( FGameplayTag& InActionTag )
{
	if( AbilitySystemComponent == nullptr )
	{
		UE_LOG( LogTemp , Warning , TEXT( "GxAction : No Ability System Component set" ) );
		return false;
	}
/*	if( CurrentActionTag != FGameplayTag::EmptyTag )
	{
		if( InNewActionNode->AbilityTag == CurrentActionTag )
		{
			UE_LOG( LogTemp , Warning , TEXT( "GxAction : Error execute the same Action" ) );

			return false;
		}
	}
*/
	FGameplayTagContainer Container;
	Container.AddTag( InActionTag );

	// if the Activation succeed, made the node the new active one
	if( AbilitySystemComponent->TryActivateAbilitiesByTag( Container ) )
	{
		// Cancel the current Node
		if( CurrentActionTag != FGameplayTag::EmptyTag )
		{
			FGameplayTag PreviousAbilityTag	=	CurrentActionTag;
//			AbilitySystemComponent->CancelExAbility( PreviousAbilityTag );
		}

		CurrentActionTag	=	InActionTag;
		CurrentState		=	EGxActionState::ActionInProgres;

		return true;
	}


	return false;
}
//---------------------------------------------------------------------------------------------
