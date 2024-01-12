// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GasExGraphLink.generated.h"


class UGasExGraphNodeBase;

/**
 *
 */
UCLASS()
class GASEX_API UGasExGraphLink : public UObject
{
	GENERATED_BODY()

public:

	/** Owning Node */
	UPROPERTY( VisibleAnywhere ,BlueprintReadOnly )
	TObjectPtr<UGasExGraphNodeBase> StartNode;

	/** Next Action Node to play */
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly  )
	TObjectPtr<UGasExGraphNodeBase> EndNode;

};
