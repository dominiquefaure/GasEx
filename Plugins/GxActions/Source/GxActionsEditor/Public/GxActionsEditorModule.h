// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IAssetTypeActions;

class FGxActionsEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:

	void RegisterAssetTypeAction( class IAssetTools& AssetTools , TSharedRef<IAssetTypeActions> Action );

private:

	/** All created asset type actions. Cached here so that we can unregister it during shutdown. */
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

	void OnPostEngineInit();

};
