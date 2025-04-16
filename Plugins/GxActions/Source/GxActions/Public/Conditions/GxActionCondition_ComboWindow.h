// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GxActionCondition_Base.h"
#include "GxActionCondition_ComboWindow.generated.h"

UCLASS( EditInlineNew )
class GXACTIONS_API UGxActionCondition_ComboWindow : public UGxActionCondition_Base
{
	GENERATED_BODY()

public:

	/*
	* Name of the combo window that must be active to satisfy this Condition.
	*/
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString WindowName	=	"Default";


	virtual bool EvaluateCondition( const FGxActionContext& InContext ) const override;

};