// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "GraphEditor/GasExEdGraphEditor.h"


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

#include "GraphEditor/Schema/GasExEdGraph_EdGraphSchema.h"


#define LOCTEXT_NAMESPACE "EGSActionGraphAssetEditor"

namespace UGasExEdGraphEditorTabs
{
	static const FName AppIdentifier( "UGasExEdGraphEditorApp" );
	static const FName GraphEditorID( "GraphEditor" );
	static const FName PropertyDetailsID( "Details" );
}

//---------------------------------------------------------------------------------------------
FGasExEdGraphEditor::FGasExEdGraphEditor()
	: GraphEdited( nullptr )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FGasExEdGraphEditor::~FGasExEdGraphEditor()
{
}
//---------------------------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------------------------
UGasExEdGraph_EdGraph* FGasExEdGraphEditor::GetAbilityEditorGraph()
{
	return Cast< UGasExEdGraph_EdGraph>( GraphEdited->EdGraph );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGasExEdGraphEditor::CreatePersonaToolkit()
{
	check( GraphEdited );

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
FName FGasExEdGraphEditor::GetToolkitFName() const
{
	return FName( "GasExEdGraphEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdGraphEditor::GetBaseToolkitName() const
{
	return LOCTEXT( "GasExEdGraphEditor" , "Ability Graph Editor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdGraphEditor::GetToolkitName() const
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
FText FGasExEdGraphEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolkitToolTipText();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FString FGasExEdGraphEditor::GetWorldCentricTabPrefix() const
{
	return TEXT( "GasExEdGraphEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FLinearColor FGasExEdGraphEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdGraphEditor::InitGraphEditor( const EToolkitMode::Type InMode , const TSharedPtr<IToolkitHost>& InInitToolkitHost , UGasExGraph* InActionGraph )
{
	UE_LOG( LogGasExEditor , Verbose , TEXT( "FEGSActionGraphAssetEditor::InitActionGraphEditor" ) );

	check( InActionGraph );

	GraphEdited = InActionGraph;

	CreateEdGraph();

	CreateWidgets();
	/*
		CreatePersonaToolkit();
		SetupComboGraphEditor(Mode, InitToolkitHost);

		RebuildComboGraph();
	*/
	TSharedRef<FTabManager::FLayout> TabLayout	=	CreateTabLayout();

	FAssetEditorToolkit::InitAssetEditor( InMode , InInitToolkitHost , UGasExEdGraphEditorTabs::AppIdentifier , TabLayout , true , true , InActionGraph );

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
TSharedRef<FTabManager::FLayout> FGasExEdGraphEditor::CreateTabLayout()
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
					->AddTab( UGasExEdGraphEditorTabs::GraphEditorID , ETabState::OpenedTab )->SetHideTabWell( true )
				)
				->Split
				(
					FTabManager::NewStack()
					->SetHideTabWell( true )
					->AddTab( UGasExEdGraphEditorTabs::PropertyDetailsID , ETabState::OpenedTab )
				)
			)
		);

	return Layout;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdGraphEditor::CreateEdGraph()
{
	if( GraphEdited->EdGraph == nullptr )
	{
		GraphEdited->EdGraph = FBlueprintEditorUtils::CreateNewGraph( GraphEdited , "Graph" , UGasExEdGraph_EdGraph::StaticClass() , UGasExEdGraph_EdGraphSchema::StaticClass() );

		GraphEdited->EdGraph->bAllowDeletion	=	false;

		// Give the schema a chance to fill out any required nodes (like the results node)
		const UEdGraphSchema* Schema = GraphEdited->EdGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph( *GraphEdited->EdGraph );
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
void FGasExEdGraphEditor::CreateWidgets()
{
	GraphEditorWidget = CreateGraphEditorWidget( GraphEdited->EdGraph );
	CreateDetailWidget();
}
//---------------------------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------------------------
TSharedRef<SGraphEditor> FGasExEdGraphEditor::CreateGraphEditorWidget( UEdGraph* InGraph )
{
	SGraphEditor::FGraphEditorEvents Events;
	Events.OnSelectionChanged	=	SGraphEditor::FOnSelectionChanged::CreateSP( this , &FGasExEdGraphEditor::OnSelectedNodesChanged );

	return SNew( SGraphEditor )
		.AdditionalCommands( GraphEditorCommands )
		.IsEditable( true )
		.GraphToEdit( InGraph )
		.GraphEvents( Events );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdGraphEditor::CreateDetailWidget()
{
	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;
	//	Args.NotifyHook = this;

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
void FGasExEdGraphEditor::RegisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory( LOCTEXT( "FGasExEdGraphEditorWorkspaceMenu" , "Ability Graph Editor" ) );
	const TSharedRef<FWorkspaceItem> WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners( InTabManager );

	InTabManager->RegisterTabSpawner( UGasExEdGraphEditorTabs::GraphEditorID , FOnSpawnTab::CreateSP( this , &FGasExEdGraphEditor::SpawnTab_GraphEditor ) )
		.SetDisplayName( LOCTEXT( "GraphTab" , "Graph" ) )
		.SetGroup( WorkspaceMenuCategoryRef );

	InTabManager->RegisterTabSpawner( UGasExEdGraphEditorTabs::PropertyDetailsID , FOnSpawnTab::CreateSP( this , &FGasExEdGraphEditor::SpawnTab_Details ) )
		.SetDisplayName( LOCTEXT( "DetailsTab" , "Property" ) )
		.SetGroup( WorkspaceMenuCategoryRef );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdGraphEditor::UnregisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	FAssetEditorToolkit::UnregisterTabSpawners( InTabManager );

	InTabManager->UnregisterTabSpawner( UGasExEdGraphEditorTabs::GraphEditorID );
	InTabManager->UnregisterTabSpawner( UGasExEdGraphEditorTabs::PropertyDetailsID );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FGasExEdGraphEditor::SpawnTab_GraphEditor( const FSpawnTabArgs& Args )
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
TSharedRef<SDockTab> FGasExEdGraphEditor::SpawnTab_Details( const FSpawnTabArgs& Args )
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
void FGasExEdGraphEditor::AddReferencedObjects( FReferenceCollector& Collector )
{
	Collector.AddReferencedObject( GraphEdited );
	Collector.AddReferencedObject( GraphEdited->EdGraph );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FString FGasExEdGraphEditor::GetReferencerName() const
{
	return TEXT( "FGasExEdGraphEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdGraphEditor::OnSelectedNodesChanged( const TSet<UObject*>& Nodes )
{
	TArray<UObject*> SelectedObjects;

	if( Nodes.Num() > 0 )
	{
		//		FlowAssetEditor.Pin()->SetUISelectionState( FFlowAssetEditor::GraphTab );

		for( TSet<UObject*>::TConstIterator SetIt( Nodes ); SetIt; ++SetIt )
		{
			if( const UGasExEdGraph_EdNodeBase* GraphNode = Cast<UGasExEdGraph_EdNodeBase>( *SetIt ) )
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
