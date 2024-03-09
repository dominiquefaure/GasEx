// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "ActionGraph/AssetTypes/GasExEdActionGraph_AssetTypeActions.h"
#include "Core/Actions/GasExActionGraph.h"
#include "GasExEditorLog.h"

#include "ActionGraph/GasExEdActionGraphEditor.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_AssetTypeActions"

//---------------------------------------------------------------------------------------------
FGasExEdActionGraph_AssetTypeActions::FGasExEdActionGraph_AssetTypeActions( const EAssetTypeCategories::Type InAssetCategory )
	: AssetCategory( InAssetCategory )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdActionGraph_AssetTypeActions::GetName() const
{
	return LOCTEXT( "FGasExEdActionGraph_AssetTypeActions" , "ActionGraph" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UClass* FGasExEdActionGraph_AssetTypeActions::GetSupportedClass() const
{
	return UGasExActionGraph::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FColor FGasExEdActionGraph_AssetTypeActions::GetTypeColor() const
{
	return FColor( 129 , 96 , 128 );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
uint32 FGasExEdActionGraph_AssetTypeActions::GetCategories()
{
	return AssetCategory;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGasExEdActionGraph_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{

	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for( auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt )
	{
		UE_LOG( LogGasExEditor , Verbose , TEXT( "Graph OpenAssetEditor ... %s" ) , *GetNameSafe( *ObjIt ) );

		auto Graph = Cast<UGasExActionGraph>( *ObjIt );

		if( Graph != nullptr )
		{
			TSharedRef<FGasExEdActionGraphEditor> AssetEditor	=	MakeShareable( new FGasExEdActionGraphEditor() );
			AssetEditor->InitGraphEditor( Mode , EditWithinLevelEditor , Graph );
		}
	}

}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
