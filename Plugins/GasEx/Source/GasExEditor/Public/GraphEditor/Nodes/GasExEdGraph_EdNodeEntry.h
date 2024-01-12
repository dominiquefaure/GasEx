// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNode.h"
#include "GraphEditor/Nodes/GasExEdGraph_EdNodeBase.h"
#include "GasExEdGraph_EdNodeEntry.generated.h"

class UEdGraph;
class UEdGraphPin;
class UEdGraphSchema;

UCLASS()
class GASEXEDITOR_API UGasExEdGraph_EdNodeEntry : public UGasExEdGraph_EdNodeBase
{
	GENERATED_BODY()

public:

	// UEdGraphNode
	virtual void AllocateDefaultPins() override;

	virtual FText GetNodeTitle( ENodeTitleType::Type ) const override {
		return FText::FromString( "Entry" );
	};
	virtual bool CanUserDeleteNode() const override {
		return false;
	}
	virtual bool CanDuplicateNode() const override {
		return false;
	}


};
