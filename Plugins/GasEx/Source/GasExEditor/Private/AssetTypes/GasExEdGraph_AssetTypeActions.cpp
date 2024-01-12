// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "AssetTypes/GasExEdGraph_AssetTypeActions.h"
#include "Core/AbilityGraph/GasExGraph.h"

#define LOCTEXT_NAMESPACE "FGasExEdGraph_AssetTypeActions"

//---------------------------------------------------------------------------------------------
FGasExEdGraph_AssetTypeActions::FGasExEdGraph_AssetTypeActions( const EAssetTypeCategories::Type InAssetCategory )
	: AssetCategory( InAssetCategory )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdGraph_AssetTypeActions::GetName() const
{
	return LOCTEXT( "FGasExEdGraph_AssetTypeActions" , "AbilityGraph" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UClass* FGasExEdGraph_AssetTypeActions::GetSupportedClass() const
{
	return UGasExGraph::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FColor FGasExEdGraph_AssetTypeActions::GetTypeColor() const
{
	return FColor( 129 , 96 , 128 );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
uint32 FGasExEdGraph_AssetTypeActions::GetCategories()
{
	return AssetCategory;
}
//---------------------------------------------------------------------------------------------

/*
//---------------------------------------------------------------------------------------------
void FGasExEdGraph_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
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
