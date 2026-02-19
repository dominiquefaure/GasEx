// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "GxInputProcessor.generated.h"

class UGxInputComponent;
class UInputAction;
struct FInputActionValue;

/**
 * Base class for input processors that manage and process specific input actions.
 * Each processor is responsible for handling one or more input actions.
 * Processors are stored in a GxInputConfig DataAsset and managed by GxInputComponent.
 * 
 * Derived classes should override the dedicated input callback methods to handle their specific actions.
 * Derived classes must override IsManagingInputAction to determine which input actions they manage.
 * Example: Movement processor, Combat processor, UI processor, etc.
 */
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class GXINPUT_API UGxInputProcessor : public UObject
{
	GENERATED_BODY()

public:

	UGxInputProcessor();

	/**
	 * Called when the owning input component initializes this processor.
	 * Override in derived classes to setup additional state or validation.
	 * @param InputComponent The input component that owns this processor
	 */
	virtual void OnRegister(UGxInputComponent* InputComponent);

	/**
	 * Called when the processor is being unregistered from the input component.
	 * Override in derived classes to cleanup state.
	 */
	virtual void OnUnregister();

	/**
	 * Check if this processor manages a specific input action.
	 * Derived classes must override this method to define their managed input actions.
	 * @param InputAction The input action to check
	 * @return true if this processor manages the input action
	 */
	UFUNCTION(BlueprintCallable, Category = "Input Processor")
	virtual bool IsManagingInputAction( UInputAction* InputAction ) const
	{
		return false;
	}

	/**
	 * Get the owning input component
	 */
	UFUNCTION(BlueprintCallable, Category = "Input Processor")
	UGxInputComponent* GetInputComponent() const { return OwningInputComponent; }

	/**
	 * Get the owning actor
	 * @return The actor that owns the input component, or nullptr if not found
	 */
	UFUNCTION(BlueprintCallable, Category = "Input Processor")
	AActor* GetOwningActor() const;


protected:

	/** The input component that owns this processor */
	UPROPERTY(Transient)
	TObjectPtr<UGxInputComponent> OwningInputComponent;

	friend class UGxInputComponent;
};