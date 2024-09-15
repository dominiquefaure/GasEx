// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "GasExEdActionSequence_EdGraph.generated.h"

class UGasExActionSequence;

UCLASS()
class UGasExEdActionSequence_EdGraph : public UEdGraph
{
	GENERATED_BODY()

public:

	UGasExEdActionSequence_EdGraph();
	virtual ~UGasExEdActionSequence_EdGraph();

	// UEdGraph
	virtual void NotifyGraphChanged() override;

	// called when a connection have been made between 2 pins : generate the necessary ActionLink
	void OnConnectionAdded( UEdGraphPin* PinA , UEdGraphPin* PinB );

	/** Returns the ActionGraph that contains this graph */
	UGasExActionSequence* GetOwnerGraph() const;

};
