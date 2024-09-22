// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbility.h"
#include "GasExActionNodeBase.h"
#include "GasExActionNodeChained.generated.h"


UENUM()
enum class EGasExActionChainType : uint8
{
	Finished		=	0 , // The Action will try to trigger when the Previous one have finished
	Always			=	1 , // Can cancel the previous action at any time
	CancelWindow	=	2 , // Can cancel the Previous action immediately if Input is done during the specified Cancel Window
};


/**
 * 
 */
UCLASS()
class GASEX_API UGasExActionNodeChained : public UGasExActionNodeBase
{
	GENERATED_BODY()

public:


	// how does this action chain with the previous one
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	EGasExActionChainType ChainType;

	// name of the Cancel Window, if needed
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FString CancelWindow;

};
