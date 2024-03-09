// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "GasExEditorModule.h"

#include "AssetToolsModule.h"
#include "AssetTypes/GasExEdAbilitySet_AssetTypeActions.h"
#include "AssetTypes/GasExEdGraph_AssetTypeActions.h"

#include "ActionGraph/AssetTypes/GasExEdActionGraph_AssetTypeActions.h"


#define LOCTEXT_NAMESPACE "FGasExEditorModule"

//---------------------------------------------------------------------------------------------
void FGasExEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Register asset types
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>( "AssetTools" ).Get();
	EAssetTypeCategories::Type AssetCategory = AssetTools.RegisterAdvancedAssetCategory( FName( TEXT( "GasEx" ) ) , FText::FromName( TEXT( "GasEx" ) ) );

	RegisterAssetTypeAction( AssetTools , MakeShareable( new FGasExEdAbilitySet_AssetTypeActions( AssetCategory ) ) );
	RegisterAssetTypeAction( AssetTools , MakeShareable( new FGasExEdGraph_AssetTypeActions( AssetCategory ) ) );
	RegisterAssetTypeAction( AssetTools , MakeShareable( new FGasExEdActionGraph_AssetTypeActions(AssetCategory ) ) );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEditorModule::ShutdownModule()
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
void FGasExEditorModule::RegisterAssetTypeAction( IAssetTools& AssetTools , TSharedRef<IAssetTypeActions> Action )
{
	AssetTools.RegisterAssetTypeActions( Action );
	CreatedAssetTypeActions.Add( Action );
}
//---------------------------------------------------------------------------------------------


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE( FGasExEditorModule , GasExEditorModule )