// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNode.h"
#include "GasExEdActionGraphNodeBase.generated.h"

class UEdGraph;
class UEdGraphPin;
class UEdGraphSchema;

class UGasExActionNode;

UCLASS( MinimalAPI , abstract )
class UGasExEdActionGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:

	UPROPERTY( Instanced )
	TObjectPtr<UGasExActionNode> RuntimeNode;

};
