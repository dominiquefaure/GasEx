// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Actions/GasExActionNode.h"
#include "GasExActionNodeLink.generated.h"

class UGasExActionNode;

UENUM()
enum class EGasExActionLinkType : uint8
{
	Finished , // The next action will try to trigger when the current action finished
	CancelWindow , // The next action will try to trigger during defined cancel windows
};


UENUM()
enum class EGasExActionCancelWindowType
{
	Immediate ,
	End
};


/**
 *
 */
UCLASS()
class GASEX_API UGasExActionNodeLink : public UObject
{
	GENERATED_BODY()

public:

	/** Owning Node */
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly )
	TObjectPtr<UGasExActionNode> SourceNode;

	/** Next Action Node to play */
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly )
	TObjectPtr<UGasExActionNode> TargetNode;


	UPROPERTY( VisibleAnywhere , BlueprintReadOnly )
	EGasExActionLinkType LinkType;
};
