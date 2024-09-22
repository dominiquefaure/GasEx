// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Actions/AssetTypes/GasExEdActionSequence_AssetTypeActions.h"
#include "Actions/GasExActionSequence.h"
#include "ActionSequence/GasExEdActionSequenceEditor.h"
#include "GasExEditorLog.h"


#define LOCTEXT_NAMESPACE "FGasExEdActionSequence_AssetTypeActions"

//---------------------------------------------------------------------------------------------
FGasExEdActionSequence_AssetTypeActions::FGasExEdActionSequence_AssetTypeActions( const EAssetTypeCategories::Type InAssetCategory )
	: AssetCategory( InAssetCategory )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdActionSequence_AssetTypeActions::GetName() const
{
	return LOCTEXT( "FGasExEdActionSequence_AssetTypeActions" , "Action Sequence" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UClass* FGasExEdActionSequence_AssetTypeActions::GetSupportedClass() const
{
	return UGasExActionSequence::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FColor FGasExEdActionSequence_AssetTypeActions::GetTypeColor() const
{
	return FColor( 129 , 96 , 128 );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
uint32 FGasExEdActionSequence_AssetTypeActions::GetCategories()
{
	return AssetCategory;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGasExEdActionSequence_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{

	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for( auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt )
	{
		UE_LOG( LogGasExEditor , Verbose , TEXT( "Graph OpenAssetEditor ... %s" ) , *GetNameSafe( *ObjIt ) );

		auto Graph = Cast<UGasExActionSequence>( *ObjIt );

		if( Graph != nullptr )
		{
			TSharedRef<FGasExEdActionSequenceEditor> AssetEditor	=	MakeShareable( new FGasExEdActionSequenceEditor() );
			AssetEditor->InitGraphEditor( Mode , EditWithinLevelEditor , Graph );
		}
	}

}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
