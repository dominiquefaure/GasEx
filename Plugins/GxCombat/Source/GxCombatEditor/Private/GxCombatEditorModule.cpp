// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "GxCombatEditorModule.h"

#include "AssetToolsModule.h"
#include "GxCombat/Public/GxWeaponHitComponent.h"
#include "GxHitComponentVisualizer.h"
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"


#define LOCTEXT_NAMESPACE "FGxCombatEditorModule"

//---------------------------------------------------------------------------------------------
void FGxCombatEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Register asset types
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>( "AssetTools" ).Get();


	if( GUnrealEd )
	{
		TSharedPtr<FGxHitComponentVisualizer> Visualizer = MakeShareable( new FGxHitComponentVisualizer() );
		GUnrealEd->RegisterComponentVisualizer( UGxWeaponHitComponent::StaticClass()->GetFName() , Visualizer );
		Visualizer->OnRegister();
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxCombatEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Unregister asset type actions
	if( FModuleManager::Get().IsModuleLoaded( "AssetTools" ) )
	{
		IAssetTools& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>( "AssetTools" ).Get();
		for( auto& AssetTypeAction : CreatedAssetTypeActions )
		{
			if( AssetTypeAction.IsValid() )
			{
				AssetToolsModule.UnregisterAssetTypeActions( AssetTypeAction.ToSharedRef() );
			}
		}
	}
	CreatedAssetTypeActions.Empty();


	if( GUnrealEd )
	{
		GUnrealEd->UnregisterComponentVisualizer( UGxWeaponHitComponent::StaticClass()->GetFName() );
	}

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxCombatEditorModule::RegisterAssetTypeAction( IAssetTools& AssetTools , TSharedRef<IAssetTypeActions> Action )
{
	AssetTools.RegisterAssetTypeActions( Action );
	CreatedAssetTypeActions.Add( Action );
}
//---------------------------------------------------------------------------------------------


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE( FGxCombatEditorModule , GxCombatEditorModule )