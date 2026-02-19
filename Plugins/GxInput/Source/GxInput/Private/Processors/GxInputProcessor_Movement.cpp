// Copyright Dominique Faure. All Rights Reserved.

#include "Processors/GxInputProcessor_Movement.h"
#include "GxInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "InputAction.h"

UGxInputProcessor_Movement::UGxInputProcessor_Movement()
{
	MoveAction = nullptr;
}

//---------------------------------------------------------------------------------------------
bool UGxInputProcessor_Movement::IsManagingInputAction(UInputAction* InputAction) const
{
	if (InputAction == nullptr)
	{
		return false;
	}

	return InputAction == MoveAction;
}
//---------------------------------------------------------------------------------------------

void UGxInputProcessor_Movement::OnRegister(UGxInputComponent* InputComponent)
{
	Super::OnRegister(InputComponent);

	// Bind move action directly to dedicated functions
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent->GetOwner()->FindComponentByClass<UInputComponent>()))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UGxInputProcessor_Movement::OnMoveTriggered);
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Completed, this, &UGxInputProcessor_Movement::OnMoveCompleted);
		}
	}
}

//---------------------------------------------------------------------------------------------
void UGxInputProcessor_Movement::OnMoveTriggered(const FInputActionValue& Value)
{
	if (ACharacter* Character = Cast<ACharacter>(OwningInputComponent->GetOwner()))
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		
		if (APlayerController* PC = Cast<APlayerController>(Character->GetController()))
		{
			const FRotator Rotation = PC->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			Character->AddMovementInput(ForwardDirection, MovementVector.Y);
			Character->AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}
//---------------------------------------------------------------------------------------------

void UGxInputProcessor_Movement::OnMoveCompleted()
{
	// Optional: Handle move completion
}
//---------------------------------------------------------------------------------------------