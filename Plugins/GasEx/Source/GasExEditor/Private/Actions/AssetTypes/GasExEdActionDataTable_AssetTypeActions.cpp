// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Actions/AssetTypes/GasExEdActionDataTable_AssetTypeActions.h"
#include "Actions/GasExActionDataTable.h"
#include "GasExEditorLog.h"
#include "DataTableEditorModule.h"


#define LOCTEXT_NAMESPACE "FGasExEdActionSequence_AssetTypeActions"

//---------------------------------------------------------------------------------------------
FGasExEdActionDataTable_AssetTypeActions::FGasExEdActionDataTable_AssetTypeActions( const EAssetTypeCategories::Type InAssetCategory )
	: AssetCategory( InAssetCategory )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdActionDataTable_AssetTypeActions::GetName() const
{
	return LOCTEXT( "FGasExEdActionSequence_AssetTypeActions" , "Action DataTable" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UClass* FGasExEdActionDataTable_AssetTypeActions::GetSupportedClass() const
{
	return UGasExActionDataTable::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FColor FGasExEdActionDataTable_AssetTypeActions::GetTypeColor() const
{
	return FColor( 129 , 96 , 128 );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
uint32 FGasExEdActionDataTable_AssetTypeActions::GetCategories()
{
	return AssetCategory;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGasExEdActionDataTable_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	TArray<UDataTable*> DataTablesToOpen;
	TArray<UDataTable*> InvalidDataTables;

	for( UObject* Obj : InObjects )
	{
		UDataTable* Table = Cast<UDataTable>( Obj );
		if( Table )
		{
			if( Table->GetRowStruct() )
			{
				DataTablesToOpen.Add( Table );
			}
			else
			{
				InvalidDataTables.Add( Table );
			}
		}
	}

	if( InvalidDataTables.Num() > 0 )
	{
		FTextBuilder DataTablesListText;
		DataTablesListText.Indent();
		for( UDataTable* Table : InvalidDataTables )
		{
			const FTopLevelAssetPath ResolvedRowStructName = Table->GetRowStructPathName();
			DataTablesListText.AppendLineFormat( LOCTEXT( "DataTable_MissingRowStructListEntry" , "* {0} (Row Structure: {1})" ) , FText::FromString( Table->GetName() ) , FText::FromString( ResolvedRowStructName.ToString() ) );
		}

		const EAppReturnType::Type DlgResult = FMessageDialog::Open(
			EAppMsgType::YesNoCancel ,
			FText::Format( LOCTEXT( "DataTable_MissingRowStructMsg" , "The following Data Tables are missing their row structure and will not be editable.\n\n{0}\n\nDo you want to open these data tables?" ) , DataTablesListText.ToText() ) ,
			LOCTEXT( "DataTable_MissingRowStructTitle" , "Continue?" )
		);

		switch( DlgResult )
		{
		case EAppReturnType::Yes:
		DataTablesToOpen.Append( InvalidDataTables );
		break;
		case EAppReturnType::Cancel:
		return;
		default:
		break;
		}
	}

	FDataTableEditorModule& DataTableEditorModule = FModuleManager::LoadModuleChecked<FDataTableEditorModule>( "DataTableEditor" );
	for( UDataTable* Table : DataTablesToOpen )
	{
		DataTableEditorModule.CreateDataTableEditor( EToolkitMode::Standalone , EditWithinLevelEditor , Table );
	}

}
//---------------------------------------------------------------------------------------------


#undef LOCTEXT_NAMESPACE
