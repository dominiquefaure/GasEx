// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GasExActionDataTable.generated.h"

class UGasExActionSequence;

USTRUCT( BlueprintType )
struct GASEX_API FGasExActionSequenceRow : public FTableRowBase
{
	GENERATED_BODY()

	FGasExActionSequenceRow();

	/** The Action sequence */
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TObjectPtr<UGasExActionSequence> ActionSequence = nullptr;

	/** can This Sequence break others on going Sequence? **/
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	bool CanBreakOthers;
};

/**
 * 
 */
UCLASS( BlueprintType )
class GASEX_API UGasExActionDataTable : public UDataTable
{
	GENERATED_BODY()

	UGasExActionDataTable();
	virtual ~UGasExActionDataTable() = default;

};
