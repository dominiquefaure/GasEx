// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Processors/GxInputProcessor.h"
#include "GxInputProcessor_Movement.generated.h"

class UInputAction;

/**
 * Input processor for character movement input.
 * Handles movement input exclusively.
 */
UCLASS()
class GXINPUT_API UGxInputProcessor_Movement : public UGxInputProcessor
{
	GENERATED_BODY()

public:

	UGxInputProcessor_Movement();

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Input")
	TObjectPtr<UInputAction> MoveAction;

	/**
	 * Check if this processor manages a specific input action.
	 * Returns true if the input action is Move.
	 */
	virtual bool IsManagingInputAction(UInputAction* InputAction) const override;

protected:

	virtual void OnRegister(UGxInputComponent* InputComponent) override;

private:

	void OnMoveTriggered(const FInputActionValue& Value);
	void OnMoveCompleted();
};