// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNode.h"
#include "GxEdComboGraph_EdNodeBase.generated.h"

class UEdGraph;
class UEdGraphPin;
class UEdGraphSchema;
class UGxComboNode_Base;

UCLASS( MinimalAPI , abstract )
class UGxEdComboGraph_EdNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:

	UPROPERTY( Instanced )
	TObjectPtr<UGxComboNode_Base> RuntimeNode;

};
