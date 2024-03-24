// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "Core/Actions/GasExActionNode.h"


class FGasExEdActionGraphUtils
{

public:

	static UEdGraphNode* CreateNode( UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , const bool bSelectNewNode , const UClass* EdNodeClass , const EGasExActionNodeType RuntimeType );

};