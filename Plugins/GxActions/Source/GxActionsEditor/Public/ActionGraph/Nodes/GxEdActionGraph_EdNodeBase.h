// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNode.h"
#include "GxEdActionGraph_EdNodeBase.generated.h"

class UEdGraph;
class UEdGraphPin;
class UEdGraphSchema;
class UGxActionNode_Base;

UCLASS( MinimalAPI , abstract )
class UGxEdActionGraph_EdNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:

	UPROPERTY( Instanced )
	TObjectPtr<UGxActionNode_Base> RuntimeNode;

};
