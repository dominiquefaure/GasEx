// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "GxActionComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GxAbilitySystemComponent.h"
#include "ActionGraph/GxActionGraph.h"
#include "ActionGraph/GxActionGraphInstance.h"


//---------------------------------------------------------------------------------------------
// Sets default values for this component's properties
UGxActionComponent::UGxActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	GraphInstance = nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// Called when the game starts
void UGxActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	AbilitySystemComponent					=	GetOwner()->GetComponentByClass<UGxAbilitySystemComponent>();
	AbilitySystemComponent->OnAbilityEnded.AddUObject( this , &UGxActionComponent::OnAbilityEnded );
	
	ExecutionContext.AbilitySystemComponent =	AbilitySystemComponent;

	UInputComponent* InputComponent			=	GetOwner()->GetComponentByClass<UInputComponent>();
	if( InputComponent != nullptr )
	{
//		RegisterInputs( InputComponent );
	}

	GraphInstance = NewObject<UGxActionGraphInstance>();
	GraphInstance->SetGraph( ActionGraph );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionComponent::OnUnregister()
{
	Super::OnUnregister();
	GraphInstance	=	nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// Called every frame
void UGxActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


	switch( ExecutionContext.CurrentState )
	{
		case EGxActionState::NoAction:
			ProcessWaitingState( );
		break;

		case EGxActionState::ActionInProgres:
			ProcessInProgressState();
		break;

		case EGxActionState::ActionFinished:
			ProcessFinishedState();
		break;
	}

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionComponent::OnInputTriggered( FGameplayTag InputTag )
{
	ExecutionContext.OnInputTriggered( InputTag );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionComponent::OnComboWindowStart( FString WindowName )
{
	if( GraphInstance != nullptr )
	{
		ExecutionContext.OnComboWindowStart( WindowName );
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionComponent::OnComboWindowEnd( FString WindowName )
{
	if( GraphInstance != nullptr )
	{
		ExecutionContext.OnComboWindowEnd( WindowName );
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionComponent::OnAbilityEnded( const FAbilityEndedData& EndedData )
{
	// if the Ability that just Ended is the Current one
	if( EndedData.AbilityThatEnded->GetAssetTags().HasTag( ExecutionContext.CurrentActionTag ) )
	{
		ExecutionContext.CurrentState		=	EGxActionState::ActionFinished;
	}
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UGxActionComponent::ProcessWaitingState()
{
	FGameplayTag InputTag	=	ExecutionContext.GetInputTag( true );
	if( InputTag != FGameplayTag::EmptyTag )
	{
		if( GraphInstance != nullptr )
		{
			GraphInstance->TryStartAction( ExecutionContext , InputTag );
		}
	}

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionComponent::ProcessInProgressState()
{
	if( GraphInstance != nullptr )
	{
		GraphInstance->UpdateCurrentAction( ExecutionContext );
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionComponent::ProcessFinishedState()
{
	bool PerformReset	=	true;

	if( GraphInstance != nullptr )
	{
		PerformReset						=	!GraphInstance->OnActionFinished( ExecutionContext );
	}

	if( PerformReset )
	{
		ResetActions();
	}

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UGxActionComponent::ResetActions()
{
	// Clear the input queue
	ExecutionContext.InputBuffer.ClearInputs();

	ExecutionContext.CurrentActionTag	=	FGameplayTag::EmptyTag;
	ExecutionContext.CurrentState		=	EGxActionState::NoAction;

	if( GraphInstance != nullptr )
	{
		GraphInstance->OnReset( );
	}
}
//---------------------------------------------------------------------------------------------
