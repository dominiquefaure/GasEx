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
	if( CurrentActionTag != FGameplayTag::EmptyTag )
	{
		if( InActionTag == CurrentActionTag )
		{
			UE_LOG( LogTemp , Warning , TEXT( "GxAction : Error execute the same Action" ) );

			return false;
		}
	}

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

		ComboWindows.Empty();

		return true;
	}


	return false;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxActionContext::OnInputTriggered( FGameplayTag InputTag )
{
	InputBuffer.OnKeyPressed( InputTag );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
const FGameplayTag FGxActionContext::GetInputTag( bool InConsume )
{
	return InputBuffer.GetInputTag( InConsume );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxActionContext::OnComboWindowStart( FString WindowName )
{
	IsCancelWindowsActive	=	true;
	ComboWindows.Add( WindowName );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxActionContext::OnComboWindowEnd( FString WindowName )
{
	int32 Index	=	-1;
	for( int32 i = 0; i < ComboWindows.Num(); i++ )
	{
		if( ComboWindows[i] == WindowName )
		{
			Index	=	i;
			break;
		}
	}

	if( Index != -1 )
	{
		ComboWindows.RemoveAt( Index );

		IsCancelWindowsActive	=	ComboWindows.Num() > 0;

	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool FGxActionContext::IsComboWindowActive( const FString& WindowName ) const
{
	int32 Index	=	-1;
	for( int32 i = 0; i < ComboWindows.Num(); i++ )
	{
		if( ComboWindows[i] == WindowName )
		{
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------------------------
