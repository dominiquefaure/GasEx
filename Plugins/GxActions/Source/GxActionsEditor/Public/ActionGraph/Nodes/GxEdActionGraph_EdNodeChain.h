// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNode.h"
#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeBase.h"
#include "GxEdActionGraph_EdNodeChain.generated.h"

class UEdGraph;
class UEdGraphPin;
class UEdGraphSchema;

UCLASS()
class GXACTIONSEDITOR_API UGxEdActionGraph_EdNodeChain : public UGxEdActionGraph_EdNodeBase
{
	GENERATED_BODY()

public:

	// UEdGraphNode
	virtual void AllocateDefaultPins() override;

	virtual FText GetNodeTitle( ENodeTitleType::Type ) const override {
		return FText::FromString( "Chain Action" );
	};
	virtual bool CanUserDeleteNode() const override {
		return false;
	}
	virtual bool CanDuplicateNode() const override {
		return false;
	}


};
