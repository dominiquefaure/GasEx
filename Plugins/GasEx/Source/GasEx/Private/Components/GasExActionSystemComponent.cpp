// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Components/GasExActionSystemComponent.h"

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
