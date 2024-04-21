// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Actions/GasExActionNode.h"
#include "GasExActionNodeLink.generated.h"

class UGasExActionNode;

UENUM()
enum class EGasExActionLinkType : uint8
{
	Finished				=	0, // The next action will try to trigger when the current action finished
	Input					=	1, // The Link required an Input, can be triggered at any moment during the Current Action. will cancel it immediately
	InputWindow				=	2, // The Link required an input, can only be triggered during a cancel window. 
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


	//UPROPERTY( VisibleAnywhere , BlueprintReadOnly )
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	EGasExActionLinkType LinkType;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FString CancelWindow;

};
