// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "AssetType/GxAttackMoveSet_AssetTypeActions.h"
#include "Attacks/GxAttackMoveSet.h"

#define LOCTEXT_NAMESPACE "FGxAttackMoveSet_AssetTypeActions"

//---------------------------------------------------------------------------------------------
FxAttackMoveSet_AssetTypeActions::FxAttackMoveSet_AssetTypeActions( const EAssetTypeCategories::Type InAssetCategory )
	: AssetCategory( InAssetCategory )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FxAttackMoveSet_AssetTypeActions::GetName() const
{
	return LOCTEXT( "FAssetTypeActions_GxAttackMoveSet" , "AttackMoveSet" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UClass* FxAttackMoveSet_AssetTypeActions::GetSupportedClass() const
{
	return UGxAttackMoveSet::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FColor FxAttackMoveSet_AssetTypeActions::GetTypeColor() const
{
	return FColor( 129 , 96 , 128 );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
uint32 FxAttackMoveSet_AssetTypeActions::GetCategories()
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
