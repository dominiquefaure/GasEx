// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "GasExEdGraph_EdGraph.generated.h"

class UGasExGraph;

UCLASS()
class UGasExEdGraph_EdGraph : public UEdGraph
{
	GENERATED_BODY()

public:

	UGasExEdGraph_EdGraph();
	virtual ~UGasExEdGraph_EdGraph();

	// UEdGraph
	virtual void NotifyGraphChanged() override;

	// called when a connection have been made between 2 pins : generate the necessary ActionLink
	void OnConnectionAdded( UEdGraphPin* PinA , UEdGraphPin* PinB );

	/** Returns the ActionGraph that contains this graph */
	UGasExGraph* GetOwnerGraph() const;

};
