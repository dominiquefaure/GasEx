// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ComboGraph/GxEdComboGraphEditor.h"

#include "Kismet2/BlueprintEditorUtils.h"

#include "Combos/GxComboGraph.h"
#include "ComboGraph/GxEdComboGraph_EdGraph.h"
#include "ComboGraph/Nodes/GxEdComboGraph_EdNodeBase.h"
#include "ComboGraph/Schema/GxEdComboGraph_EdGraphSchema.h"


#define LOCTEXT_NAMESPACE "FGxEdComboGraphEditor"

namespace FGxEdComboGraphEditorTabs
{
	static const FName AppIdentifier( "FGxEdComboGraphEditorApp" );
	static const FName GraphEditorID( "GraphEditor" );
	static const FName PropertyDetailsID( "Details" );
}


//---------------------------------------------------------------------------------------------
FGxEdComboGraphEditor::FGxEdComboGraphEditor()
	: GraphEdited( nullptr )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FGxEdComboGraphEditor::~FGxEdComboGraphEditor()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxEdComboGraphEditor::AddReferencedObjects( FReferenceCollector& Collector )
{
	//	Collector.AddReferencedObject( GraphEdited );
	//	Collector.AddReferencedObject( GraphEdited->EdGraph );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
FName FGxEdComboGraphEditor::GetToolkitFName() const
{
	return FName( "GxEdComboGraphEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGxEdComboGraphEditor::GetBaseToolkitName() const
{
	return LOCTEXT( "GxEdComboGraphEditor" , "Combo Graph Editor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGxEdComboGraphEditor::GetToolkitName() const
{
	const TArray<UObject*>& EditingObjs = GetEditingObjects();
	check( EditingObjs.Num() > 0 );

	const UObject* EditingObject = EditingObjs[0];
	check( EditingObject );

	FFormatNamedArguments Args;
	Args.Add( TEXT( "GraphName" ) , FText::FromString( EditingObject->GetName() ) );
	Args.Add( TEXT( "DirtyState" ) , EditingObject->GetOutermost()->IsDirty() ? FText::FromString( TEXT( "*" ) ) : FText::GetEmpty() );
	return FText::Format( LOCTEXT( "GxEdComboGraphEditorToolkitName" , "{GraphName}{DirtyState}" ) , Args );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGxEdComboGraphEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolkitToolTipText();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FString FGxEdComboGraphEditor::GetWorldCentricTabPrefix() const
{
	return TEXT( "GxEdComboGraphEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FLinearColor FGxEdComboGraphEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FString FGxEdComboGraphEditor::GetReferencerName() const
{
	return TEXT( "FGxEdComboGraphEditor" );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxEdComboGraphEditor::InitGraphEditor( const EToolkitMode::Type InMode , const TSharedPtr<IToolkitHost>& InInitToolkitHost , UGxComboGraph* InActionGraph )
{
	check( InActionGraph );

	GraphEdited = InActionGraph;

	CreateEdGraph();

	CreateWidgets();

	TSharedRef<FTabManager::FLayout> TabLayout	=	CreateTabLayout();

	FAssetEditorToolkit::InitAssetEditor( InMode , InInitToolkitHost , FGxEdComboGraphEditorTabs::AppIdentifier , TabLayout , true , true , InActionGraph );

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxEdComboGraphEditor::CreateEdGraph()
{

	UGxComboGroup* CurrentGroup	=	GraphEdited->Groups[ 0 ];

	if( CurrentGroup->EdGraph == nullptr )
	{
		CurrentGroup->EdGraph = FBlueprintEditorUtils::CreateNewGraph( CurrentGroup , "Graph" , UGxEdComboGraph_EdGraph::StaticClass() , UGxEdComboGraph_EdGraphSchema::StaticClass() );

		CurrentGroup->EdGraph->bAllowDeletion	=	false;

		// Give the schema a chance to fill out any required nodes (like the results node)
		const UEdGraphSchema* Schema = CurrentGroup->EdGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph( *CurrentGroup->EdGraph );
	}
	else
	{
	}
}
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
TSharedRef<FTabManager::FLayout> FGxEdComboGraphEditor::CreateTabLayout()
{
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout( "Standalone_GasExEdGraphEditor_Layout_v01" )
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation( Orient_Vertical )
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation( Orient_Horizontal )->SetSizeCoefficient( 0.9f )
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient( 0.75f )
					->AddTab( FGxEdComboGraphEditorTabs::GraphEditorID , ETabState::OpenedTab )->SetHideTabWell( true )
				)
				->Split
				(
					FTabManager::NewStack()
					->SetHideTabWell( true )
					->AddTab( FGxEdComboGraphEditorTabs::PropertyDetailsID , ETabState::OpenedTab )
				)
			)
		);

	return Layout;
}
//---------------------------------------------------------------------------------------------


//////
// Widgets creations
//////

//---------------------------------------------------------------------------------------------
void FGxEdComboGraphEditor::CreateWidgets()
{
	GraphEditorWidget = CreateGraphEditorWidget( GraphEdited->Groups[0]->EdGraph );
	CreateDetailWidget();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TSharedRef<SGraphEditor> FGxEdComboGraphEditor::CreateGraphEditorWidget( UEdGraph* InGraph )
{
	SGraphEditor::FGraphEditorEvents Events;
	Events.OnSelectionChanged	=	SGraphEditor::FOnSelectionChanged::CreateSP( this , &FGxEdComboGraphEditor::OnSelectedNodesChanged );

	return SNew( SGraphEditor )
		.AdditionalCommands( GraphEditorCommands )
		.IsEditable( true )
		.GraphToEdit( InGraph )
		.GraphEvents( Events );

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxEdComboGraphEditor::CreateDetailWidget()
{
	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>( "PropertyEditor" );
	PropertyDetailsView = PropertyModule.CreateDetailView( Args );
	PropertyDetailsView->SetObject( GraphEdited );
	//	PropertyDetailsWidget->OnFinishedChangingProperties().AddSP( this , &FAssetEditor_GenericGraph::OnFinishedChangingProperties );

}
//---------------------------------------------------------------------------------------------


//////
// Tabs Spanning
//////

//---------------------------------------------------------------------------------------------
void FGxEdComboGraphEditor::RegisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory( LOCTEXT( "FGxEdComboGraphEditorWorkspaceMenu" , "Combo Graph Editor" ) );
	const TSharedRef<FWorkspaceItem> WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners( InTabManager );

	InTabManager->RegisterTabSpawner( FGxEdComboGraphEditorTabs::GraphEditorID , FOnSpawnTab::CreateSP( this , &FGxEdComboGraphEditor::SpawnTab_GraphEditor ) )
		.SetDisplayName( LOCTEXT( "GraphTab" , "Graph" ) )
		.SetGroup( WorkspaceMenuCategoryRef );

	InTabManager->RegisterTabSpawner( FGxEdComboGraphEditorTabs::PropertyDetailsID , FOnSpawnTab::CreateSP( this , &FGxEdComboGraphEditor::SpawnTab_Details ) )
		.SetDisplayName( LOCTEXT( "DetailsTab" , "Property" ) )
		.SetGroup( WorkspaceMenuCategoryRef );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxEdComboGraphEditor::UnregisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	FAssetEditorToolkit::UnregisterTabSpawners( InTabManager );

	InTabManager->UnregisterTabSpawner( FGxEdComboGraphEditorTabs::GraphEditorID );
	InTabManager->UnregisterTabSpawner( FGxEdComboGraphEditorTabs::PropertyDetailsID );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FGxEdComboGraphEditor::SpawnTab_GraphEditor( const FSpawnTabArgs& Args )
{
	return SNew( SDockTab )
		.Label( LOCTEXT( "GraphTitle" , "Graph" ) )
		.TabColorScale( GetTabColorScale() )
		[
			GraphEditorWidget.ToSharedRef()
		];
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FGxEdComboGraphEditor::SpawnTab_Details( const FSpawnTabArgs& Args )
{
	return SNew( SDockTab )
		.Label( LOCTEXT( "DetailsTitle" , "Details" ) )
		.TabColorScale( GetTabColorScale() )
		[
			PropertyDetailsView.ToSharedRef()
		];

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxEdComboGraphEditor::OnSelectedNodesChanged( const TSet<UObject*>& Nodes )
{
	TArray<UObject*> SelectedObjects;

	if( Nodes.Num() > 0 )
	{
		//		FlowAssetEditor.Pin()->SetUISelectionState( FFlowAssetEditor::GraphTab );

		for( TSet<UObject*>::TConstIterator SetIt( Nodes ); SetIt; ++SetIt )
		{
			if( const UGxEdComboGraph_EdNodeBase* GraphNode = Cast<UGxEdComboGraph_EdNodeBase>( *SetIt ) )
			{
				SelectedObjects.Add( Cast<UObject>( GraphNode->RuntimeNode ) );
			}
			else
			{
				SelectedObjects.Add( *SetIt );
			}
		}
	}
	else
	{
		SelectedObjects.Add( GraphEdited );
	}

	if( PropertyDetailsView.IsValid() )
	{
		PropertyDetailsView->SetObjects( SelectedObjects );
	}

	//	OnSelectionChangedEvent.ExecuteIfBound( Nodes );
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
