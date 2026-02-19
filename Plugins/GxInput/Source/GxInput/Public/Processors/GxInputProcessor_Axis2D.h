// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Processors/GxInputProcessor.h"
#include "GxInputProcessor_Axis2D.generated.h"

class UInputAction;
struct FInputActionValue;

/**
 * Input processor for 2D axis input actions.
 * Exposes blueprint-callable events for axis value changes.
 * Suitable for look, aim, steering, and other continuous 2D inputs.
 */
UCLASS()
class GXINPUT_API UGxInputProcessor_Axis2D : public UGxInputProcessor
{
	GENERATED_BODY()

public:

	UGxInputProcessor_Axis2D();

	/** 2D Axis Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Axis Input")
	TObjectPtr<UInputAction> AxisAction;

	/**
	 * Check if this processor manages a specific input action.
	 * Returns true if the input action is the configured AxisAction.
	 */
	virtual bool IsManagingInputAction(UInputAction* InputAction) const override;

	/**
	 * Blueprint event called when the axis value is triggered (axis is being used).
	 * @param AxisValue The 2D axis value (typically in range [-1, 1])
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Axis Input")
	void OnAxisTriggered(FVector2D AxisValue);

	/**
	 * Blueprint event called when the axis input is completed (axis is released).
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Axis Input")
	void OnAxisCompleted();

	/**
	 * Blueprint event called whenever axis value changes while active.
	 * Called every frame the axis input is triggered.
	 * @param AxisValue The current 2D axis value
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Axis Input")
	void OnAxisChanged(FVector2D AxisValue);

protected:

	virtual void OnRegister(UGxInputComponent* InputComponent) override;

private:

	void OnAxisActionTriggered(const FInputActionValue& Value);
	void OnAxisActionCompleted(const FInputActionValue& Value);

	/** Cached previous axis value to detect changes */
	FVector2D CachedAxisValue;

	/** Whether the axis is currently active */
	bool bIsAxisActive;
};