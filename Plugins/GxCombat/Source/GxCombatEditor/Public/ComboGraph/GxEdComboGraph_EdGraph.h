// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "GxEdComboGraph_EdGraph.generated.h"

class UGxComboGraph;
class UGxComboGroup;

UCLASS()
class UGxEdComboGraph_EdGraph : public UEdGraph
{
	GENERATED_BODY()

public:

	UGxEdComboGraph_EdGraph();
	virtual ~UGxEdComboGraph_EdGraph();

	// UEdGraph
	virtual void NotifyGraphChanged() override;

	// called when a connection have been made between 2 pins : generate the necessary ActionLink
	void OnConnectionAdded( UEdGraphPin* PinA , UEdGraphPin* PinB );

	/** Returns the ActionGraph that contains this graph */
	UGxComboGroup* GetOwnerGraph() const;

};
