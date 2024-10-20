// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Actions/AssetTypes/GasExEdActionSet_AssetTypeActions.h"
#include "Actions/GasExActionSet.h"
#include "GasExEditorLog.h"


#define LOCTEXT_NAMESPACE "FGasExEdActionSet_AssetTypeActions"

//---------------------------------------------------------------------------------------------
FGasExEdActionSet_AssetTypeActions::FGasExEdActionSet_AssetTypeActions( const EAssetTypeCategories::Type InAssetCategory )
	: AssetCategory( InAssetCategory )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdActionSet_AssetTypeActions::GetName() const
{
	return LOCTEXT( "FGasExEdActionSet_AssetTypeActions" , "Action Set" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UClass* FGasExEdActionSet_AssetTypeActions::GetSupportedClass() const
{
	return UGasExActionSet::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FColor FGasExEdActionSet_AssetTypeActions::GetTypeColor() const
{
	return FColor( 129 , 96 , 128 );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
uint32 FGasExEdActionSet_AssetTypeActions::GetCategories()
{
	return AssetCategory;
}
//---------------------------------------------------------------------------------------------

/*
//---------------------------------------------------------------------------------------------
void FGasExEdActionSet_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{

}
//---------------------------------------------------------------------------------------------
*/

#undef LOCTEXT_NAMESPACE
