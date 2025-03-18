// Copyright 2023-2024 Dominique Faure. All Rights Reserved.



#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "GxEdActionGraph_EdGraphSchema.generated.h"

class UEdGraphPin;
class FConnectionDrawingPolicy;


UCLASS( MinimalAPI )
class UGxEdActionGraph_EdGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:

	// EdGraphSchema
	virtual void CreateDefaultNodesForGraph( UEdGraph& Graph ) const override;

	/** Get all actions that can be performed when right clicking on a graph or drag-releasing on a graph from a pin */
	virtual void GetGraphContextActions( FGraphContextMenuBuilder& ContextMenuBuilder ) const override;

	virtual const FPinConnectionResponse CanCreateConnection( const UEdGraphPin* PinA , const UEdGraphPin* PinB ) const override;
	virtual bool TryCreateConnection( UEdGraphPin* A , UEdGraphPin* B ) const override;


private:
	void GetCommentAction( FGraphActionMenuBuilder& ActionMenuBuilder );

	void GetNewNodesActions( FGraphActionMenuBuilder& ActionMenuBuilder , const UEdGraph* CurrentGraph = nullptr ) const;

};
