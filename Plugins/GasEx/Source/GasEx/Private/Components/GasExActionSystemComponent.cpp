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
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// Called when the game starts
void UGasExActionSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystem	=	GetOwner()->GetComponentByClass<UGasExAbilitySystemComponent>();


	GraphInstance = NewObject<UGasExActionGraphInstance>();
	GraphInstance->SetGraph(ActionGraph);
	GraphInstance->SetAbilitySystem(AbilitySystem);

	UInputComponent* InputComponent	=	GetOwner()->GetComponentByClass<UInputComponent>();
	if( InputComponent != nullptr )
	{
		RegisterInputs( InputComponent );
	}

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// Called every frame
void UGasExActionSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSystemComponent::TestFirstAction()
{
	GraphInstance->LaunchFirstAction();
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
//			EnhancedInputComponent->BindAction( InputAction.InputAction , ETriggerEvent::Triggered , this , &UGasExActionSystemComponent::OnInputTriggered , InputAction.InputTag );
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
	check( GraphInstance );

	GraphInstance->ProcessInputTriggered( InputTag );
}
//---------------------------------------------------------------------------------------------
