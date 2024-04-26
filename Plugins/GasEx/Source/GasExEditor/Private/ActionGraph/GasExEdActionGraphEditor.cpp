// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GasExEdActionGraphEditor.h"


#include "AnimCustomInstanceHelper.h"
#include "AnimPreviewInstance.h"
#include "AnimationEditorPreviewActor.h"
#include "EdGraphUtilities.h"
#include "GraphEditorActions.h"
#include "IPersonaEditorModeManager.h"
#include "IPersonaPreviewScene.h"
#include "IPersonaToolkit.h"
#include "PersonaModule.h"
#include "Animation/DebugSkelMeshComponent.h"
#include "Framework/Commands/GenericCommands.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Kismet2/BlueprintEditorUtils.h"
//#include "Persona/Private/AnimationEditorPreviewScene.h"
#include "Runtime/Launch/Resources/Version.h"
#include "UObject/ObjectSaveContext.h"

#include "GasExEditorLog.h"

#include "ActionGraph/GasExEdActionGraph_EdGraph.h"
#include "ActionGraph/Schema/GasExEdActionGraph_EdGraphSchema.h"


#define LOCTEXT_NAMESPACE "FGasExEdActionGraphEditor"

namespace UGasExEdActionGraphEditorTabs
{
	static const FName AppIdentifier( "UGasExEdGraphEditorApp" );
	static const FName GraphEditorID( "GraphEditor" );
	static const FName PropertyDetailsID( "Details" );
}

//---------------------------------------------------------------------------------------------
FGasExEdActionGraphEditor::FGasExEdActionGraphEditor()
	: ActionGraphEdited( nullptr )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FGasExEdActionGraphEditor::~FGasExEdActionGraphEditor()
{
}
//---------------------------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------------------------
UGasExEdActionGraph_EdGraph* FGasExEdActionGraphEditor::GetActionEditorGraph()
{
	return Cast< UGasExEdActionGraph_EdGraph>(ActionGraphEdited->EdGraph );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGasExEdActionGraphEditor::CreatePersonaToolkit()
{
	check(ActionGraphEdited );

	const FPersonaModule& PersonaModule = FModuleManager::GetModuleChecked<FPersonaModule>( "Persona" );

	FPersonaToolkitArgs PersonaToolkitArgs;
	//	PersonaToolkitArgs.OnPreviewSceneCreated = FOnPreviewSceneCreated::FDelegate::CreateSP(this, &FComboGraphAssetEditor::HandlePreviewSceneCreated);
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 2
	PersonaToolkitArgs.bPreviewMeshCanUseDifferentSkeleton = true;
#endif

	/*	PersonaToolkit = PersonaModule.CreatePersonaToolkit(ComboGraphBeingEdited , PersonaToolkitArgs);
		PersonaToolkit->GetPreviewScene()->SetDefaultAnimationMode(EPreviewSceneDefaultAnimationMode::ReferencePose);
		PersonaToolkit->GetPreviewScene()->RegisterOnPreviewMeshChanged(FOnPreviewMeshChanged::CreateSP(this, &FComboGraphAssetEditor::HandlePreviewMeshChanged));

		FPersonaViewportArgs ViewportArgs(PersonaToolkit->GetPreviewScene());
		ViewportArgs.bShowStats = false;
		ViewportArgs.bShowPlaySpeedMenu = false;
		ViewportArgs.bShowTimeline = false;
		ViewportArgs.bShowTurnTable = false;
		ViewportArgs.bAlwaysShowTransformToolbar = true;
		ViewportArgs.OnViewportCreated = FOnViewportCreated::CreateSP(this, &FComboGraphAssetEditor::HandleViewportCreated);
		*/
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FName FGasExEdActionGraphEditor::GetToolkitFName() const
{
	return FName( "GasExEdGraphEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdActionGraphEditor::GetBaseToolkitName() const
{
	return LOCTEXT( "GasExEdGraphEditor" , "Ability Graph Editor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdActionGraphEditor::GetToolkitName() const
{
	const TArray<UObject*>& EditingObjs = GetEditingObjects();
	check( EditingObjs.Num() > 0 );

	const UObject* EditingObject = EditingObjs[ 0 ];
	check( EditingObject );

	FFormatNamedArguments Args;
	Args.Add( TEXT( "GraphName" ) , FText::FromString( EditingObject->GetName() ) );
	Args.Add( TEXT( "DirtyState" ) , EditingObject->GetOutermost()->IsDirty() ? FText::FromString( TEXT( "*" ) ) : FText::GetEmpty() );
	return FText::Format( LOCTEXT( "GasExEdGraphEditorToolkitName" , "{GraphName}{DirtyState}" ) , Args );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdActionGraphEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolkitToolTipText();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FString FGasExEdActionGraphEditor::GetWorldCentricTabPrefix() const
{
	return TEXT( "GasExEdGraphEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FLinearColor FGasExEdActionGraphEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdActionGraphEditor::InitGraphEditor( const EToolkitMode::Type InMode , const TSharedPtr<IToolkitHost>& InInitToolkitHost , UGasExActionGraph* InActionGraph )
{
	UE_LOG( LogGasExEditor , Verbose , TEXT( "FEGSActionGraphAssetEditor::InitActionGraphEditor" ) );

	check( InActionGraph );

	ActionGraphEdited = InActionGraph;

	CreateEdGraph();

	CreateWidgets();
	/*
		CreatePersonaToolkit();
		SetupComboGraphEditor(Mode, InitToolkitHost);

		RebuildComboGraph();
	*/
	TSharedRef<FTabManager::FLayout> TabLayout	=	CreateTabLayout();

	FAssetEditorToolkit::InitAssetEditor( InMode , InInitToolkitHost , UGasExEdActionGraphEditorTabs::AppIdentifier , TabLayout , true , true , InActionGraph );

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
TSharedRef<FTabManager::FLayout> FGasExEdActionGraphEditor::CreateTabLayout()
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
					->AddTab(UGasExEdActionGraphEditorTabs::GraphEditorID , ETabState::OpenedTab )->SetHideTabWell( true )
				)
				->Split
				(
					FTabManager::NewStack()
					->SetHideTabWell( true )
					->AddTab(UGasExEdActionGraphEditorTabs::PropertyDetailsID , ETabState::OpenedTab )
				)
			)
		);

	return Layout;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdActionGraphEditor::CreateEdGraph()
{
	if(ActionGraphEdited->EdGraph == nullptr )
	{
		ActionGraphEdited->EdGraph = FBlueprintEditorUtils::CreateNewGraph(ActionGraphEdited , "Graph" , UGasExEdActionGraph_EdGraph::StaticClass() , UGasExEdActionGraph_EdGraphSchema::StaticClass() );

		ActionGraphEdited->EdGraph->bAllowDeletion	=	false;

		// Give the schema a chance to fill out any required nodes (like the results node)
		const UEdGraphSchema* Schema = ActionGraphEdited->EdGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph( *ActionGraphEdited->EdGraph );
	}
	else
	{
	}
}
//---------------------------------------------------------------------------------------------

//////
// Widgets creations
//////

//---------------------------------------------------------------------------------------------
void FGasExEdActionGraphEditor::CreateWidgets()
{
	GraphEditorWidget = CreateGraphEditorWidget(ActionGraphEdited->EdGraph );
	CreateDetailWidget();
}
//---------------------------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------------------------
TSharedRef<SGraphEditor> FGasExEdActionGraphEditor::CreateGraphEditorWidget( UEdGraph* InGraph )
{
	SGraphEditor::FGraphEditorEvents Events;
	Events.OnSelectionChanged	=	SGraphEditor::FOnSelectionChanged::CreateSP( this , &FGasExEdActionGraphEditor::OnSelectedNodesChanged );

	return SNew( SGraphEditor )
		.AdditionalCommands( GraphEditorCommands )
		.IsEditable( true )
		.GraphToEdit( InGraph )
		.GraphEvents( Events );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdActionGraphEditor::CreateDetailWidget()
{
	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;
	//	Args.NotifyHook = this;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>( "PropertyEditor" );
	PropertyDetailsView = PropertyModule.CreateDetailView( Args );
	PropertyDetailsView->SetObject(ActionGraphEdited);
	//	PropertyDetailsWidget->OnFinishedChangingProperties().AddSP( this , &FAssetEditor_GenericGraph::OnFinishedChangingProperties );

}
//---------------------------------------------------------------------------------------------


//////
// Tabs Spanning
//////

//---------------------------------------------------------------------------------------------
void FGasExEdActionGraphEditor::RegisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory( LOCTEXT( "FGasExEdActionGraphEditorWorkspaceMenu" , "Action Graph Editor" ) );
	const TSharedRef<FWorkspaceItem> WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners( InTabManager );

	InTabManager->RegisterTabSpawner(UGasExEdActionGraphEditorTabs::GraphEditorID , FOnSpawnTab::CreateSP( this , &FGasExEdActionGraphEditor::SpawnTab_GraphEditor ) )
		.SetDisplayName( LOCTEXT( "GraphTab" , "Graph" ) )
		.SetGroup( WorkspaceMenuCategoryRef );

	InTabManager->RegisterTabSpawner(UGasExEdActionGraphEditorTabs::PropertyDetailsID , FOnSpawnTab::CreateSP( this , &FGasExEdActionGraphEditor::SpawnTab_Details ) )
		.SetDisplayName( LOCTEXT( "DetailsTab" , "Property" ) )
		.SetGroup( WorkspaceMenuCategoryRef );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdActionGraphEditor::UnregisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	FAssetEditorToolkit::UnregisterTabSpawners( InTabManager );

	InTabManager->UnregisterTabSpawner(UGasExEdActionGraphEditorTabs::GraphEditorID );
	InTabManager->UnregisterTabSpawner(UGasExEdActionGraphEditorTabs::PropertyDetailsID );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FGasExEdActionGraphEditor::SpawnTab_GraphEditor( const FSpawnTabArgs& Args )
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
TSharedRef<SDockTab> FGasExEdActionGraphEditor::SpawnTab_Details( const FSpawnTabArgs& Args )
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
void FGasExEdActionGraphEditor::AddReferencedObjects( FReferenceCollector& Collector )
{
//	Collector.AddReferencedObject(ActionGraphEdited);
//	Collector.AddReferencedObject(ActionGraphEdited->EdGraph );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FString FGasExEdActionGraphEditor::GetReferencerName() const
{
	return TEXT( "FGasExEdActionGraphEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdActionGraphEditor::OnSelectedNodesChanged( const TSet<UObject*>& Nodes )
{
	TArray<UObject*> SelectedObjects;

	if (Nodes.Num() > 0)
	{
		//		FlowAssetEditor.Pin()->SetUISelectionState( FFlowAssetEditor::GraphTab );

		for( TSet<UObject*>::TConstIterator SetIt( Nodes ); SetIt; ++SetIt )
		{
			if( const UGasExEdActionGraphNodeBase* GraphNode = Cast<UGasExEdActionGraphNodeBase>( *SetIt ) )
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
		//		FlowAssetEditor.Pin()->SetUISelectionState( NAME_None );
		SelectedObjects.Add(ActionGraphEdited);
	}

	if( PropertyDetailsView.IsValid() )
	{
		PropertyDetailsView->SetObjects( SelectedObjects );
	}
}
//---------------------------------------------------------------------------------------------


#undef LOCTEXT_NAMESPACE
