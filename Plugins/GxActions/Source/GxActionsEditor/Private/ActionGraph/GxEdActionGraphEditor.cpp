// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxEdActionGraphEditor.h"

#include "Kismet2/BlueprintEditorUtils.h"

#include "ActionGraph/GxActionGraph.h"
#include "ActionGraph/GxActionGroup.h"
#include "ActionGraph/GxEdActionGraph_EdGraph.h"
#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeBase.h"
#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchema.h"


#define LOCTEXT_NAMESPACE "FGxEdActionGraphEditor"

namespace FGxEdActionGraphEditorTabs
{
	static const FName AppIdentifier( "FGxEdActionGraphEditorApp" );
	static const FName GraphEditorID( "GraphEditor" );
	static const FName PropertyDetailsID( "Details" );
}


//---------------------------------------------------------------------------------------------
FGxEdActionGraphEditor::FGxEdActionGraphEditor()
	: GraphEdited( nullptr )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FGxEdActionGraphEditor::~FGxEdActionGraphEditor()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxEdActionGraphEditor::AddReferencedObjects( FReferenceCollector& Collector )
{
	//	Collector.AddReferencedObject( GraphEdited );
	//	Collector.AddReferencedObject( GraphEdited->EdGraph );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
FName FGxEdActionGraphEditor::GetToolkitFName() const
{
	return FName( "GxEdActionGraphEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGxEdActionGraphEditor::GetBaseToolkitName() const
{
	return LOCTEXT( "GxEdActionGraphEditor" , "Action Graph Editor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGxEdActionGraphEditor::GetToolkitName() const
{
	const TArray<UObject*>& EditingObjs = GetEditingObjects();
	check( EditingObjs.Num() > 0 );

	const UObject* EditingObject = EditingObjs[0];
	check( EditingObject );

	FFormatNamedArguments Args;
	Args.Add( TEXT( "GraphName" ) , FText::FromString( EditingObject->GetName() ) );
	Args.Add( TEXT( "DirtyState" ) , EditingObject->GetOutermost()->IsDirty() ? FText::FromString( TEXT( "*" ) ) : FText::GetEmpty() );
	return FText::Format( LOCTEXT( "GxEdActionGraphEditorToolkitName" , "{GraphName}{DirtyState}" ) , Args );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGxEdActionGraphEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolkitToolTipText();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FString FGxEdActionGraphEditor::GetWorldCentricTabPrefix() const
{
	return TEXT( "GxEdActionGraphEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FLinearColor FGxEdActionGraphEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FString FGxEdActionGraphEditor::GetReferencerName() const
{
	return TEXT( "FGxEdActionGraphEditor" );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxEdActionGraphEditor::InitGraphEditor( const EToolkitMode::Type InMode , const TSharedPtr<IToolkitHost>& InInitToolkitHost , UGxActionGraph* InActionGraph )
{
	check( InActionGraph );

	GraphEdited = InActionGraph;

	CreateEdGraph();

	CreateWidgets();

	TSharedRef<FTabManager::FLayout> TabLayout	=	CreateTabLayout();

	FAssetEditorToolkit::InitAssetEditor( InMode , InInitToolkitHost , FGxEdActionGraphEditorTabs::AppIdentifier , TabLayout , true , true , InActionGraph );

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxEdActionGraphEditor::CreateEdGraph()
{

	UGxActionGroup* CurrentGroup	=	GraphEdited->Groups[ 0 ];

	if( CurrentGroup->EdGraph == nullptr )
	{
		CurrentGroup->EdGraph = FBlueprintEditorUtils::CreateNewGraph( CurrentGroup , "Graph" , UGxEdActionGraph_EdGraph::StaticClass() , UGxEdActionGraph_EdGraphSchema::StaticClass() );

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
TSharedRef<FTabManager::FLayout> FGxEdActionGraphEditor::CreateTabLayout()
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
					->AddTab( FGxEdActionGraphEditorTabs::GraphEditorID , ETabState::OpenedTab )->SetHideTabWell( true )
				)
				->Split
				(
					FTabManager::NewStack()
					->SetHideTabWell( true )
					->AddTab( FGxEdActionGraphEditorTabs::PropertyDetailsID , ETabState::OpenedTab )
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
void FGxEdActionGraphEditor::CreateWidgets()
{
	GraphEditorWidget = CreateGraphEditorWidget( GraphEdited->Groups[0]->EdGraph );
	CreateDetailWidget();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TSharedRef<SGraphEditor> FGxEdActionGraphEditor::CreateGraphEditorWidget( UEdGraph* InGraph )
{
	SGraphEditor::FGraphEditorEvents Events;
	Events.OnSelectionChanged	=	SGraphEditor::FOnSelectionChanged::CreateSP( this , &FGxEdActionGraphEditor::OnSelectedNodesChanged );

	return SNew( SGraphEditor )
		.AdditionalCommands( GraphEditorCommands )
		.IsEditable( true )
		.GraphToEdit( InGraph )
		.GraphEvents( Events );

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxEdActionGraphEditor::CreateDetailWidget()
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
void FGxEdActionGraphEditor::RegisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory( LOCTEXT( "FGxEdActionGraphEditorWorkspaceMenu" , "Action Graph Editor" ) );
	const TSharedRef<FWorkspaceItem> WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners( InTabManager );

	InTabManager->RegisterTabSpawner( FGxEdActionGraphEditorTabs::GraphEditorID , FOnSpawnTab::CreateSP( this , &FGxEdActionGraphEditor::SpawnTab_GraphEditor ) )
		.SetDisplayName( LOCTEXT( "GraphTab" , "Graph" ) )
		.SetGroup( WorkspaceMenuCategoryRef );

	InTabManager->RegisterTabSpawner( FGxEdActionGraphEditorTabs::PropertyDetailsID , FOnSpawnTab::CreateSP( this , &FGxEdActionGraphEditor::SpawnTab_Details ) )
		.SetDisplayName( LOCTEXT( "DetailsTab" , "Property" ) )
		.SetGroup( WorkspaceMenuCategoryRef );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGxEdActionGraphEditor::UnregisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	FAssetEditorToolkit::UnregisterTabSpawners( InTabManager );

	InTabManager->UnregisterTabSpawner( FGxEdActionGraphEditorTabs::GraphEditorID );
	InTabManager->UnregisterTabSpawner( FGxEdActionGraphEditorTabs::PropertyDetailsID );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FGxEdActionGraphEditor::SpawnTab_GraphEditor( const FSpawnTabArgs& Args )
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
TSharedRef<SDockTab> FGxEdActionGraphEditor::SpawnTab_Details( const FSpawnTabArgs& Args )
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
void FGxEdActionGraphEditor::OnSelectedNodesChanged( const TSet<UObject*>& Nodes )
{
	TArray<UObject*> SelectedObjects;

	if( Nodes.Num() > 0 )
	{
		//		FlowAssetEditor.Pin()->SetUISelectionState( FFlowAssetEditor::GraphTab );

		for( TSet<UObject*>::TConstIterator SetIt( Nodes ); SetIt; ++SetIt )
		{
			if( const UGxEdActionGraph_EdNodeBase* GraphNode = Cast<UGxEdActionGraph_EdNodeBase>( *SetIt ) )
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
