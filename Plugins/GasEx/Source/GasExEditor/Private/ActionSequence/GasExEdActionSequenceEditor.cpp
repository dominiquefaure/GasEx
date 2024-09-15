// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionSequence/GasExEdActionSequenceEditor.h"


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

#include "Actions/GasExActionSequence.h"
#include "ActionSequence/GasExEdActionSequence_EdGraph.h"
#include "ActionSequence/Nodes/GasExEdActionSequence_EdNodeBase.h"
#include "ActionSequence/Schema/GasExEdActionSequence_EdGraphSchema.h"


#define LOCTEXT_NAMESPACE "FGasExEdActionSequenceEditor"

namespace FGasExEdActionSequenceEditorTabs
{
	static const FName AppIdentifier( "UGasExEdGraphEditorApp" );
	static const FName GraphEditorID( "GraphEditor" );
	static const FName PropertyDetailsID( "Details" );
}

//---------------------------------------------------------------------------------------------
FGasExEdActionSequenceEditor::FGasExEdActionSequenceEditor()
	: GraphEdited( nullptr )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FGasExEdActionSequenceEditor::~FGasExEdActionSequenceEditor()
{
}
//---------------------------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------------------------
UGasExEdActionSequence_EdGraph* FGasExEdActionSequenceEditor::GetAbilityEditorGraph()
{
	return Cast< UGasExEdActionSequence_EdGraph>( GraphEdited->EdGraph );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FGasExEdActionSequenceEditor::CreatePersonaToolkit()
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
FName FGasExEdActionSequenceEditor::GetToolkitFName() const
{
	return FName( "GasExEdActionSequenceEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdActionSequenceEditor::GetBaseToolkitName() const
{
	return LOCTEXT( "GasExEdGraphEditor" , "Ability Graph Editor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText FGasExEdActionSequenceEditor::GetToolkitName() const
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
FText FGasExEdActionSequenceEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolkitToolTipText();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FString FGasExEdActionSequenceEditor::GetWorldCentricTabPrefix() const
{
	return TEXT( "GasExEdActionSequenceEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FLinearColor FGasExEdActionSequenceEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdActionSequenceEditor::InitGraphEditor( const EToolkitMode::Type InMode , const TSharedPtr<IToolkitHost>& InInitToolkitHost , UGasExActionSequence* InActionGraph )
{
	UE_LOG( LogGasExEditor , Verbose , TEXT( "FEGSActionGraphAssetEditor::InitActionGraphEditor" ) );

	check( InActionGraph );

	GraphEdited = InActionGraph;

	CreateEdGraph();

	CreateWidgets();

	TSharedRef<FTabManager::FLayout> TabLayout	=	CreateTabLayout();

	FAssetEditorToolkit::InitAssetEditor( InMode , InInitToolkitHost , FGasExEdActionSequenceEditorTabs::AppIdentifier , TabLayout , true , true , InActionGraph );

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
TSharedRef<FTabManager::FLayout> FGasExEdActionSequenceEditor::CreateTabLayout()
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
					->AddTab( FGasExEdActionSequenceEditorTabs::GraphEditorID , ETabState::OpenedTab )->SetHideTabWell( true )
				)
				->Split
				(
					FTabManager::NewStack()
					->SetHideTabWell( true )
					->AddTab( FGasExEdActionSequenceEditorTabs::PropertyDetailsID , ETabState::OpenedTab )
				)
			)
		);

	return Layout;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdActionSequenceEditor::CreateEdGraph()
{
	if( GraphEdited->EdGraph == nullptr )
	{
		GraphEdited->EdGraph = FBlueprintEditorUtils::CreateNewGraph( GraphEdited , "Graph" , UGasExEdActionSequence_EdGraph::StaticClass() , UGasExEdActionSequence_EdGraphSchema::StaticClass() );

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
void FGasExEdActionSequenceEditor::CreateWidgets()
{
	GraphEditorWidget = CreateGraphEditorWidget( GraphEdited->EdGraph );
	CreateDetailWidget();
}
//---------------------------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------------------------
TSharedRef<SGraphEditor> FGasExEdActionSequenceEditor::CreateGraphEditorWidget( UEdGraph* InGraph )
{
	SGraphEditor::FGraphEditorEvents Events;
	Events.OnSelectionChanged	=	SGraphEditor::FOnSelectionChanged::CreateSP( this , &FGasExEdActionSequenceEditor::OnSelectedNodesChanged );

	return SNew( SGraphEditor )
		.AdditionalCommands( GraphEditorCommands )
		.IsEditable( true )
		.GraphToEdit( InGraph )
		.GraphEvents( Events );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdActionSequenceEditor::CreateDetailWidget()
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
void FGasExEdActionSequenceEditor::RegisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory( LOCTEXT( "FGasExEdGraphEditorWorkspaceMenu" , "Ability Graph Editor" ) );
	const TSharedRef<FWorkspaceItem> WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners( InTabManager );

	InTabManager->RegisterTabSpawner( FGasExEdActionSequenceEditorTabs::GraphEditorID , FOnSpawnTab::CreateSP( this , &FGasExEdActionSequenceEditor::SpawnTab_GraphEditor ) )
		.SetDisplayName( LOCTEXT( "GraphTab" , "Graph" ) )
		.SetGroup( WorkspaceMenuCategoryRef );

	InTabManager->RegisterTabSpawner( FGasExEdActionSequenceEditorTabs::PropertyDetailsID , FOnSpawnTab::CreateSP( this , &FGasExEdActionSequenceEditor::SpawnTab_Details ) )
		.SetDisplayName( LOCTEXT( "DetailsTab" , "Property" ) )
		.SetGroup( WorkspaceMenuCategoryRef );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdActionSequenceEditor::UnregisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	FAssetEditorToolkit::UnregisterTabSpawners( InTabManager );

	InTabManager->UnregisterTabSpawner( FGasExEdActionSequenceEditorTabs::GraphEditorID );
	InTabManager->UnregisterTabSpawner( FGasExEdActionSequenceEditorTabs::PropertyDetailsID );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FGasExEdActionSequenceEditor::SpawnTab_GraphEditor( const FSpawnTabArgs& Args )
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
TSharedRef<SDockTab> FGasExEdActionSequenceEditor::SpawnTab_Details( const FSpawnTabArgs& Args )
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
void FGasExEdActionSequenceEditor::AddReferencedObjects( FReferenceCollector& Collector )
{
//	Collector.AddReferencedObject( GraphEdited );
//	Collector.AddReferencedObject( GraphEdited->EdGraph );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FString FGasExEdActionSequenceEditor::GetReferencerName() const
{
	return TEXT( "FGasExEdActionSequenceEditor" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGasExEdActionSequenceEditor::OnSelectedNodesChanged( const TSet<UObject*>& Nodes )
{
	TArray<UObject*> SelectedObjects;

	if( Nodes.Num() > 0 )
	{
		//		FlowAssetEditor.Pin()->SetUISelectionState( FFlowAssetEditor::GraphTab );

		for( TSet<UObject*>::TConstIterator SetIt( Nodes ); SetIt; ++SetIt )
		{
			if( const UGasExEdActionSequence_EdNodeBase* GraphNode = Cast<UGasExEdActionSequence_EdNodeBase>( *SetIt ) )
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
