// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "AssetType/GxComboGraph_AssetTypeActions.h"
#include "Combos/GxComboGraph.h"
#include "ComboGraph/GxEdComboGraphEditor.h"


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


//---------------------------------------------------------------------------------------------
void FxGxComboGraph_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{

	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for( auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt )
	{

		auto Graph = Cast<UGxComboGraph>( *ObjIt );

		if( Graph != nullptr )
		{
			TSharedRef<FGxEdComboGraphEditor> AssetEditor	=	MakeShareable( new FGxEdComboGraphEditor() );
			AssetEditor->InitGraphEditor( Mode , EditWithinLevelEditor , Graph );
		}
	}

}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
