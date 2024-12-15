// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Components/GasExActionSystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



//---------------------------------------------------------------------------------------------
// Sets default values for this component's properties
UGasExActionSystemComponent::UGasExActionSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	SequenceInstance	=	nullptr;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// Called when the game starts
void UGasExActionSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystem	=	GetOwner()->GetComponentByClass<UGasExAbilitySystemComponent>();

	UInputComponent* InputComponent	=	GetOwner()->GetComponentByClass<UInputComponent>();
	if( InputComponent != nullptr )
	{
		RegisterInputs( InputComponent );
	}

	ActionSets.Add( DefaultActionSet );

	/*
		GraphInstance = NewObject<UGasExActionGraphInstance>();
		GraphInstance->SetGraph(ActionGraph);
		GraphInstance->SetAbilitySystem(AbilitySystem);
	*/
	SequenceInstance = NewObject<UGasExActionSequenceInstance>(this);
	SequenceInstance->SetAbilitySystem( AbilitySystem );
//	SequenceInstance->SetSequence( ActionSequence );
	SequenceInstance->AddActionSet( DefaultActionSet );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSystemComponent::OnUnregister()
{
	Super::OnUnregister();
	//	GraphInstance	=	nullptr;
	SequenceInstance	=	nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// Called every frame
void UGasExActionSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if( SequenceInstance != nullptr )
	{
		SequenceInstance->Tick();
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSystemComponent::RegisterInputs( UInputComponent* PlayerInputComponent )
{
	check( InputConfig )

	// Set up action bindings
	if( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>( PlayerInputComponent ) ) 
	{
		for( FGasExInputAction& InputAction : InputConfig->InputActions )
		{
			EnhancedInputComponent->BindAction( InputAction.InputAction , ETriggerEvent::Started , this , &UGasExActionSystemComponent::OnInputTriggered , InputAction.InputTag );
		}
	}
	else
	{
	}

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSystemComponent::OnInputTriggered( FGameplayTag InputTag )
{
	if( SequenceInstance != nullptr )
	{
		SequenceInstance->OnInputTriggered( InputTag );
	}
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UGasExActionSystemComponent::OnCancelWindowStart( FString WindowName )
{
	if( SequenceInstance != nullptr )
	{
		SequenceInstance->OnCancelWindowStart( WindowName );
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSystemComponent::OnCancelWindowEnd( FString WindowName )
{
	if( SequenceInstance != nullptr )
	{
		SequenceInstance->OnCancelWindowEnd( WindowName );
	}
}
//---------------------------------------------------------------------------------------------
