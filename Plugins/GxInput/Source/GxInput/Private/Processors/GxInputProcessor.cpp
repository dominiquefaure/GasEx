// Copyright Dominique Faure. All Rights Reserved.

#include "Processors/GxInputProcessor.h"
#include "GxInputComponent.h"
#include "InputAction.h"

//---------------------------------------------------------------------------------------------
UGxInputProcessor::UGxInputProcessor()
	: OwningInputComponent(nullptr)
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxInputProcessor::OnRegister(UGxInputComponent* InputComponent)
{
	OwningInputComponent = InputComponent;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxInputProcessor::OnUnregister()
{
	OwningInputComponent = nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
AActor* UGxInputProcessor::GetOwningActor() const
{
	if (OwningInputComponent != nullptr)
	{
		return OwningInputComponent->GetOwner();
	}
	return nullptr;
}
//---------------------------------------------------------------------------------------------


