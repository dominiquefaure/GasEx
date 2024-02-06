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

//	AbilityFailedCallbacks.AddUObject( this , &UGasExAbilitySystemComponent::ProcessAbilityFail );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGasExAbilitySystemComponent::TryActivateExAbility( const FGameplayTag& AbilityTag )
{
	FGasExAbilitySetRow* AbilityDef	=	GetAbilityDef( AbilityTag );

	if( AbilityDef != nullptr )
	{
		if( AbilityDef->UseCustomParameters )
		{
			FGameplayAbilityActorInfo ActorInfo;
			FGameplayEventData EventData;

			EventData.OptionalObject	=	AbilityDef->Parameters;
			return TriggerAbilityFromGameplayEvent( AbilityDef->AbilitySpec.Handle , &ActorInfo , FGameplayTag::EmptyTag , &EventData , *this );

		}
		else
		{
			return TryActivateAbility( AbilityDef->AbilitySpec.Handle );
		}
	}
	else
	{
		// use default method as fallback
		FGameplayTagContainer Container;
		Container.AddTag( AbilityTag );

		return TryActivateAbilitiesByTag( Container , true );
	}
	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExAbilitySystemComponent::CancelExAbility( const FGameplayTag& AbilityTag )
{
	FGasExAbilitySetRow* AbilityDef	=	GetAbilityDef( AbilityTag );

	if( AbilityDef != nullptr )
	{
		CancelAbilityHandle( AbilityDef->AbilitySpec.Handle );
	}
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

//-----------------------------------------------------------------------------------------
void UGasExAbilitySystemComponent::NotifyAbilityFailed( const FGameplayAbilitySpecHandle Handle , UGameplayAbility* Ability , const FGameplayTagContainer& FailureReason )
{
	UE_LOG( LogTemp , Warning , TEXT( "Activity failed : %s" ) , *( Ability->GetPathName() ) );

	
}
//-----------------------------------------------------------------------------------------
