// Copyright Dominique Faure. All Rights Reserved.

#include "GxInputComponent.h"
#include "Processors/GxInputProcessor.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"

//-----------------------------------------------------------------------------------------
UGxInputComponent::UGxInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ActiveInputConfig = nullptr;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxInputComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultInputConfig != nullptr)
	{
		SetInputConfig(DefaultInputConfig);
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxInputComponent::SetInputConfig(UGxInputConfig* NewConfig)
{
	// Shutdown previous processors
	ShutdownInputProcessors();

	ActiveInputConfig = NewConfig;
	InstanceInputProcessors();
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxInputComponent::InstanceInputProcessors()
{
	InstancedInputProcessors.Empty();

	if (ActiveInputConfig)
	{
		for (UGxInputProcessor* Processor : ActiveInputConfig->InputProcessors)
		{
			if (Processor)
			{
				UGxInputProcessor* NewProcessor = DuplicateObject<UGxInputProcessor>(Processor, this);
				NewProcessor->OnRegister(this);
				InstancedInputProcessors.Add(NewProcessor);
			}
		}
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxInputComponent::ShutdownInputProcessors()
{
	for (UGxInputProcessor* Processor : InstancedInputProcessors)
	{
		if (Processor)
		{
			Processor->OnUnregister();
		}
	}
	InstancedInputProcessors.Empty();
}
//-----------------------------------------------------------------------------------------

