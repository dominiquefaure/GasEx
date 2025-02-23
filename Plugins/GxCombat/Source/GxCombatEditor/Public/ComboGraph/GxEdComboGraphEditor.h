// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class IPersonaToolkit;
class IPersonaPreviewScene;
class UAnimPreviewInstance;

class UGxComboGraph;
class UGxEdComboGraph_EdGraph;


class GXCOMBATEDITOR_API FGxEdComboGraphEditor : public FAssetEditorToolkit , public FNotifyHook , public FGCObject
{
public:
	FGxEdComboGraphEditor();
	virtual ~FGxEdComboGraphEditor();

	/**
	 * Edits the specified gameplay ability asset(s) with a specialized interface
	 *
	 * @param	Mode					Asset editing mode for this editor (standalone or world-centric)
	 * @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within
	 * @param	InComboGraph				The graph model to edit
	 */
	void InitGraphEditor( const EToolkitMode::Type Mode , const TSharedPtr<IToolkitHost>& InitToolkitHost , UGxComboGraph* InComboGraph );


	/** Get the graph being edited */
	UGxEdComboGraph_EdGraph* GetCurrentGraphEditor();


	// Interfaces Overrides
public:

	//~ Begin IToolkit Interface
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	virtual void RegisterTabSpawners( const TSharedRef<FTabManager>& InTabManager ) override;
	virtual void UnregisterTabSpawners( const TSharedRef<FTabManager>& InTabManager ) override;
	//~ End of IToolkit Interface

	//~ Begin FGCObject Interface
	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;
	virtual FString GetReferencerName() const override;
	//~ End FGCObject Interface

private:


	TSharedRef<FTabManager::FLayout> CreateTabLayout();

	void CreateEdGraph();

	//--------------------------------
	// Widgets creation
	//--------------------------------

	// create the different Widgets that will be used in the editor
	void CreateWidgets();

	// create the Widget that allow to inspect the properties of an Object
	void CreateDetailWidget();

	TSharedRef<SGraphEditor> CreateGraphEditorWidget( UEdGraph* InGraph );


	//--------------------------------
	// Tab Spawnings 
	//--------------------------------

	TSharedRef<SDockTab> SpawnTab_GraphEditor( const FSpawnTabArgs& Args );
	TSharedRef<SDockTab> SpawnTab_Details( const FSpawnTabArgs& Args );

protected:
	virtual void OnSelectedNodesChanged( const TSet<UObject*>& Nodes );


	// members properties
private:

	/** The Combo Graph model this editor handles */
	TObjectPtr<UGxComboGraph> GraphEdited;



	// the Widgetss

	// The Widget that allow to compose the Graph
	TSharedPtr<SGraphEditor> GraphEditorWidget;

	//The widget that allow to see the properties of an Object 
	TSharedPtr<IDetailsView> PropertyDetailsView;

	// Command list for the graph editor
	TSharedPtr<FUICommandList> GraphEditorCommands;

};
