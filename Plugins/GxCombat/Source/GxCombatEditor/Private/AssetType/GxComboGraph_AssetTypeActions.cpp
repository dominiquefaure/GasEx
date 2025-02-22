// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "AssetType/GxComboGraph_AssetTypeActions.h"
#include "Combos/GxComboGraph.h"

#define LOCTEXT_NAMESPACE "FGxComboGraph_AssetTypeActions"

//---------------------------------------------------------------------------------------------
FxGxComboGraph_AssetTypeActions::FxGxComboGraph_AssetTypeActions( const EAssetTypeCategories::Type InAssetCategory )
	: AssetCategory( InAssetCategory )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FxGxComboGraph_AssetTypeActions::GetName() const
{
	return LOCTEXT( "FxGxComboGraph_AssetTypeActions" , "ComboGraph" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UClass* FxGxComboGraph_AssetTypeActions::GetSupportedClass() const
{
	return UGxComboGraph::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FColor FxGxComboGraph_AssetTypeActions::GetTypeColor() const
{
	return FColor( 255 , 96 , 128 );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
uint32 FxGxComboGraph_AssetTypeActions::GetCategories()
{
	return AssetCategory;
}
//---------------------------------------------------------------------------------------------

/*
//---------------------------------------------------------------------------------------------
void FxAttackMoveSet_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
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
