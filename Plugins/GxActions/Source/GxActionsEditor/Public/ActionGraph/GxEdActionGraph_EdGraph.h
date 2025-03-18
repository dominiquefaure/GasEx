// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "GxEdActionGraph_EdGraph.generated.h"

class UGxActionGraph;
class UGxActionGroup;

UCLASS()
class UGxEdActionGraph_EdGraph : public UEdGraph
{
	GENERATED_BODY()

public:

	UGxEdActionGraph_EdGraph();
	virtual ~UGxEdActionGraph_EdGraph();

	// UEdGraph
	virtual void NotifyGraphChanged() override;

	// called when a connection have been made between 2 pins : generate the necessary ActionLink
	void OnConnectionAdded( UEdGraphPin* PinA , UEdGraphPin* PinB );

	/** Returns the ActionGraph that contains this graph */
	UGxActionGroup* GetOwnerGraph() const;

};
