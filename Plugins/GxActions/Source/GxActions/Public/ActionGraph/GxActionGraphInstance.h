// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GxActionContext.h"
#include "GxActionGraphInstance.generated.h"

class UGxAbilitySystemComponent;
class UGxActionGraph;
class UGxActionNode_Base;


/**
 *
 */
UCLASS()
class GXACTIONS_API UGxActionGraphInstance : public UObject
{
	GENERATED_BODY()

public:

	UGxActionGraphInstance();


	void SetGraph(UGxActionGraph* Graph);



	bool TryStartAction( FGxActionContext& ExecutionContext , FGameplayTag InInputTag );

	/*
	* allow to launch additional action when the current one is finished
	* only Next action can be launched
	*/
	bool OnActionFinished( FGxActionContext& ExecutionContext );


	void OnReset();


	void UpdateCurrentAction( FGxActionContext& ExecutionContext );




private:



	// the Graph instanciated
	TObjectPtr<UGxActionGraph>				Graph;
	TObjectPtr<UGxActionNode_Base>			CurrentGraphNode;


};