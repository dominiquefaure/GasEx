// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNode.h"
#include "GasExEdActionSequence_EdNodeBase.generated.h"

class UEdGraph;
class UEdGraphPin;
class UEdGraphSchema;
class UGasExActionNodeBase;

UCLASS( MinimalAPI , abstract )
class UGasExEdActionSequence_EdNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:

	UPROPERTY( Instanced )
	TObjectPtr<UGasExActionNodeBase> RuntimeNode;

};
