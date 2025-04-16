// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GxActionContext.h"
#include "GxActionCondition_Base.generated.h"

UCLASS( abstract)
class GXACTIONS_API UGxActionCondition_Base : public UObject
{
	GENERATED_BODY()

public:

	virtual bool EvaluateCondition( const FGxActionContext& InContext )const;
};