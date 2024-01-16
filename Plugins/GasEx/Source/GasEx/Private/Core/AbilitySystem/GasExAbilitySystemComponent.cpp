// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Core/AbilitySystem/GasExAbilitySystemComponent.h"
#include "Core/AbilitySystem/GasExAbilitySet.h"

//-----------------------------------------------------------------------------------------
UGasExAbilitySystemComponent::UGasExAbilitySystemComponent( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	if( DefaultAbilitySet != nullptr )
	{
		DefaultAbilitySet->Register( this );
	}

	GraphInstance	=	NewObject<UGasExGraphInstance>( );
	GraphInstance->SetGraph( DefaultAbilityGraph );
	GraphInstance->SetAbilitySystem( this );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGasExAbilitySystemComponent::TryActivateExAbility( const FGameplayTag& AbilityTag )
{
	FGasExAbilitySetRow* AbilityDef	=	GetAbilityDef( AbilityTag );

	if( AbilityDef != nullptr )
	{
		return TryActivateAbility( AbilityDef->AbilitySpec.Handle );

	}
	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FGasExAbilitySetRow* UGasExAbilitySystemComponent::GetAbilityDef( const FGameplayTag& AbilityTag )
{
	FGasExAbilitySetRow* AbilityDef	=	nullptr;

	if( DefaultAbilitySet )
	{
		AbilityDef	=	DefaultAbilitySet->GetAbilityRow( AbilityTag );

		if( AbilityDef != nullptr )
		{
			return AbilityDef;
		}
	}


	return nullptr;
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
void UGasExAbilitySystemComponent::TryActivateNextGraphNode()
{
	GraphInstance->TryExecuteNextNode();
}
//-----------------------------------------------------------------------------------------
