// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "AssetTypes/GasExEdAbilitySet_AssetTypeActions.h"
#include "Core/AbilitySystem/GasExAbilitySet.h"

#define LOCTEXT_NAMESPACE "FGasExEdAbilitySet_AssetTypeActions"

//---------------------------------------------------------------------------------------------
FGasExEdAbilitySet_AssetTypeActions::FGasExEdAbilitySet_AssetTypeActions(const EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdAbilitySet_AssetTypeActions::GetName() const
{
	return LOCTEXT("FAssetTypeActions_GasExAbilitySet", "AbilitySet");
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UClass* FGasExEdAbilitySet_AssetTypeActions::GetSupportedClass() const
{
	return UGasExAbilitySet::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FColor FGasExEdAbilitySet_AssetTypeActions::GetTypeColor() const
{
	return FColor(129, 96, 128);
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
uint32 FGasExEdAbilitySet_AssetTypeActions::GetCategories()
{
	return AssetCategory;
}
//---------------------------------------------------------------------------------------------

/*
//---------------------------------------------------------------------------------------------
void FGasExEdAbilitySet_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{

	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for( auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt )
	{
		UE_LOG( LogEGSGraphEditor , Verbose , TEXT( "Action Graph OpenAssetEditor ... %s" ) , *GetNameSafe( *ObjIt ) );

		auto Graph = Cast<UEGSActionGraph>( *ObjIt );

		if( Graph != nullptr )
		{
			TSharedRef<FEGSActionGraphAssetEditor> AssetEditor	=	MakeShareable( new FEGSActionGraphAssetEditor() );
			AssetEditor->InitActionGraphEditor( Mode , EditWithinLevelEditor , Graph );
		}
	}

}
//---------------------------------------------------------------------------------------------
*/
#undef LOCTEXT_NAMESPACE
