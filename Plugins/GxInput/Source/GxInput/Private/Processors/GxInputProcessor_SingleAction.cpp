// Copyright Dominique Faure. All Rights Reserved.

#include "Processors/GxInputProcessor_SingleAction.h"
#include "GxInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

UGxInputProcessor_SingleAction::UGxInputProcessor_SingleAction()
	: InputAction(nullptr)
	, bIsActionActive(false)
{
}

//---------------------------------------------------------------------------------------------
bool UGxInputProcessor_SingleAction::IsManagingInputAction(UInputAction* InInputAction) const
{
	if (InInputAction == nullptr)
	{
		return false;
	}

	return InInputAction == InputAction;
}
//---------------------------------------------------------------------------------------------

void UGxInputProcessor_SingleAction::OnRegister(UGxInputComponent* InputComponent)
{
	Super::OnRegister(InputComponent);

	// Bind input action to dedicated functions for all trigger events
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent->GetOwner()->FindComponentByClass<UInputComponent>()))
	{
		if (InputAction)
		{
			EnhancedInput->BindAction(InputAction, ETriggerEvent::Started, this, &UGxInputProcessor_SingleAction::OnInputActionStarted);
			EnhancedInput->BindAction(InputAction, ETriggerEvent::Triggered, this, &UGxInputProcessor_SingleAction::OnInputActionTriggered);
			EnhancedInput->BindAction(InputAction, ETriggerEvent::Completed, this, &UGxInputProcessor_SingleAction::OnInputActionCompleted);
			EnhancedInput->BindAction(InputAction, ETriggerEvent::Canceled, this, &UGxInputProcessor_SingleAction::OnInputActionCancelled);
		}
	}
}

//---------------------------------------------------------------------------------------------
void UGxInputProcessor_SingleAction::OnInputActionStarted(const FInputActionValue& Value)
{
	bIsActionActive = true;
	OnActionStarted(Value);
}
//---------------------------------------------------------------------------------------------

void UGxInputProcessor_SingleAction::OnInputActionTriggered(const FInputActionValue& Value)
{
	OnActionTriggered(Value);
}
//---------------------------------------------------------------------------------------------

void UGxInputProcessor_SingleAction::OnInputActionCompleted(const FInputActionValue& Value)
{
	bIsActionActive = false;
	OnActionCompleted(Value);
}
//---------------------------------------------------------------------------------------------

void UGxInputProcessor_SingleAction::OnInputActionCancelled(const FInputActionValue& Value)
{
	bIsActionActive = false;
	OnActionCancelled();
}
//---------------------------------------------------------------------------------------------