// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "GxInputConfig.h"
#include "GxInputComponent.generated.h"

class UGxInputProcessor;

UCLASS(ClassGroup = (Gx), meta = (BlueprintSpawnableComponent))
class GXINPUT_API UGxInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UGxInputComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UGxInputConfig> DefaultInputConfig;

	/**
	 * Sets the active input configuration and initializes all processors
	 * @param NewConfig The new input configuration to activate
	 */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetInputConfig(UGxInputConfig* NewConfig);

	/**
	 * Get the current active input configuration
	 */
	UFUNCTION(BlueprintCallable, Category = "Input")
	UGxInputConfig* GetInputConfig() const { return ActiveInputConfig; }

	/**
	 * Find a processor of a specific class
	 */
	template<typename ProcessorClass>
	ProcessorClass* FindProcessor() const
	{
		for (UGxInputProcessor* Processor : InstancedInputProcessors)
		{
			if (ProcessorClass* CastedProcessor = Cast<ProcessorClass>(Processor))
			{
				return CastedProcessor;
			}
		}
		return nullptr;
	}

protected:

	virtual void BeginPlay() override;

private:

	/** The active input configuration (not directly editable at runtime) */
	UPROPERTY(Transient)
	TObjectPtr<UGxInputConfig> ActiveInputConfig;

	/** Instanced processors for runtime logic */
	UPROPERTY(Transient)
	TArray<TObjectPtr<UGxInputProcessor>> InstancedInputProcessors;

	/** Helper to instance and register processors */
	void InstanceInputProcessors();

	/** Helper to shutdown and unregister processors */
	void ShutdownInputProcessors();
};