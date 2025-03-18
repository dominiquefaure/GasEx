// Copyright Epic Games, Inc. All Rights Reserved.

#include "GxActions.h"

#define LOCTEXT_NAMESPACE "FGxCombatModule"

void FGxActionsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FGxActionsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGxActionsModule, GxActions)