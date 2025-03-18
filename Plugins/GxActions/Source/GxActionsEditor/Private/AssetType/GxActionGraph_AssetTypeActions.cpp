// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "AssetType/GxActionGraph_AssetTypeActions.h"
#include "ActionGraph/GxActionGraph.h"
#include "ActionGraph/GxEdActionGraphEditor.h"


#define LOCTEXT_NAMESPACE "FGxActionGraph_AssetTypeActions"

//---------------------------------------------------------------------------------------------
FGxActionGraph_AssetTypeActions::FGxActionGraph_AssetTypeActions( const EAssetTypeCategories::Type InAssetCategory )
	: AssetCategory( InAssetCategory )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGxActionGraph_AssetTypeActions::GetName() const
{
	return LOCTEXT( "FxGxActionGraph_AssetTypeActions" , "ActionGraph" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UClass* FGxActionGraph_AssetTypeActions::GetSupportedClass() const
{
	return UGxActionGraph::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FColor FGxActionGraph_AssetTypeActions::GetTypeColor() const
{
	return FColor( 0 , 255 , 0 );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
uint32 FGxActionGraph_AssetTypeActions::GetCategories()
{
	return AssetCategory;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxActionGraph_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{

	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for( auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt )
	{

		auto Graph = Cast<UGxActionGraph>( *ObjIt );

		if( Graph != nullptr )
		{
			TSharedRef<FGxEdActionGraphEditor> AssetEditor	=	MakeShareable( new FGxEdActionGraphEditor() );
			AssetEditor->InitGraphEditor( Mode , EditWithinLevelEditor , Graph );
		}
	}

}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
