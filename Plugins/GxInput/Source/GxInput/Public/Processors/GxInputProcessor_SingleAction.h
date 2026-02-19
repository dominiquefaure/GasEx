// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Processors/GxInputProcessor.h"
#include "GxInputProcessor_SingleAction.generated.h"

class UInputAction;
struct FInputActionValue;

/**
 * Generic input processor for a single input action.
 * Exposes blueprint-callable events for input triggered, started, and completed.
 * Suitable for any single input action (button, axis, etc.).
 */
UCLASS()
class GXINPUT_API UGxInputProcessor_SingleAction : public UGxInputProcessor
{
	GENERATED_BODY()

public:

	UGxInputProcessor_SingleAction();

	/** Input Action to manage */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Action")
	TObjectPtr<UInputAction> InputAction;

	/**
	 * Check if this processor manages a specific input action.
	 * Returns true if the input action matches the configured InputAction.
	 */
	virtual bool IsManagingInputAction(UInputAction* InInputAction) const override;

	/**
	 * Blueprint event called when the input action starts.
	 * @param ActionValue The input action value at start
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Input Action")
	void OnActionStarted(FInputActionValue ActionValue);

	/**
	 * Blueprint event called while the input action is being triggered.
	 * Called every frame the action is active.
	 * @param ActionValue The current input action value
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Input Action")
	void OnActionTriggered(FInputActionValue ActionValue);

	/**
	 * Blueprint event called when the input action is completed.
	 * @param ActionValue The final input action value
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Input Action")
	void OnActionCompleted(FInputActionValue ActionValue);

	/**
	 * Blueprint event called when the input action is cancelled.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Input Action")
	void OnActionCancelled();

protected:

	virtual void OnRegister(UGxInputComponent* InputComponent) override;

private:

	void OnInputActionStarted(const FInputActionValue& Value);
	void OnInputActionTriggered(const FInputActionValue& Value);
	void OnInputActionCompleted(const FInputActionValue& Value);
	void OnInputActionCancelled(const FInputActionValue& Value);

	/** Whether the input action is currently active */
	bool bIsActionActive;
};