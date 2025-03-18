// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"

#include "ActionGraph/GxActionNode_Base.h"

class FGxEdActionGraphUtils
{

public:

	static UEdGraphNode* CreateEditorNode( UEdGraph* ParentGraph , UEdGraphPin* FromPin , const UClass* EdNodeClass , TObjectPtr<UGxActionNode_Base> InRuntimeNode , const FVector2D Location , const bool bSelectNewNode);


	static TObjectPtr<UGxActionNode_Base> CreateRuntimeNode( UEdGraph* ParentGraph , const UClass* RuntimeClass );

};