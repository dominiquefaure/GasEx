// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "GxActionsEditorModule.h"

#include "AssetToolsModule.h"
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#include "AssetType/GxActionGraph_AssetTypeActions.h"
#include "AssetType/GxActionGraph_Factory.h"

#define LOCTEXT_NAMESPACE "FGxActionsEditorModule"

//---------------------------------------------------------------------------------------------
void FGxActionsEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

		// Register asset types
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>( "AssetTools" ).Get();
	EAssetTypeCategories::Type AssetCategory = AssetTools.RegisterAdvancedAssetCategory( FName( TEXT( "Gx" ) ) , FText::FromName( TEXT( "Gx" ) ) );

	RegisterAssetTypeAction( AssetTools , MakeShareable( new FGxActionGraph_AssetTypeActions( AssetCategory ) ) );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxActionsEditorModule::ShutdownModule()
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

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxActionsEditorModule::RegisterAssetTypeAction( IAssetTools& AssetTools , TSharedRef<IAssetTypeActions> Action )
{
	AssetTools.RegisterAssetTypeActions( Action );
	CreatedAssetTypeActions.Add( Action );
}
//---------------------------------------------------------------------------------------------


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE( FGxActionsEditorModule , GxActionsEditor )