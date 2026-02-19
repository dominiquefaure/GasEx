// Copyright Dominique Faure. All Rights Reserved.

#include "Processors/GxInputProcessor_Axis2D.h"
#include "GxInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

UGxInputProcessor_Axis2D::UGxInputProcessor_Axis2D()
	: AxisAction(nullptr)
	, CachedAxisValue(FVector2D::ZeroVector)
	, bIsAxisActive(false)
{
}

//---------------------------------------------------------------------------------------------
bool UGxInputProcessor_Axis2D::IsManagingInputAction(UInputAction* InputAction) const
{
	if (InputAction == nullptr)
	{
		return false;
	}

	return InputAction == AxisAction;
}
//---------------------------------------------------------------------------------------------

void UGxInputProcessor_Axis2D::OnRegister(UGxInputComponent* InputComponent)
{
	Super::OnRegister(InputComponent);

	// Bind axis input action to dedicated functions
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent->GetOwner()->FindComponentByClass<UInputComponent>()))
	{
		if (AxisAction)
		{
			EnhancedInput->BindAction(AxisAction, ETriggerEvent::Triggered, this, &UGxInputProcessor_Axis2D::OnAxisActionTriggered);
			EnhancedInput->BindAction(AxisAction, ETriggerEvent::Completed, this, &UGxInputProcessor_Axis2D::OnAxisActionCompleted);
		}
	}
}

//---------------------------------------------------------------------------------------------
void UGxInputProcessor_Axis2D::OnAxisActionTriggered(const FInputActionValue& Value)
{
	const FVector2D AxisValue = Value.Get<FVector2D>();

	// Check if this is the first trigger or if value has changed
	if (!bIsAxisActive)
	{
		bIsAxisActive = true;
		OnAxisTriggered(AxisValue);
	}

	// Notify of axis value change every frame
	if (!AxisValue.Equals(CachedAxisValue))
	{
		CachedAxisValue = AxisValue;
		OnAxisChanged(AxisValue);
	}
}
//---------------------------------------------------------------------------------------------

void UGxInputProcessor_Axis2D::OnAxisActionCompleted(const FInputActionValue& Value)
{
	bIsAxisActive = false;
	CachedAxisValue = FVector2D::ZeroVector;
	OnAxisCompleted();
}
//---------------------------------------------------------------------------------------------