// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTypes.h"

#include "GasExActionSequenceInstance.generated.h"

class UGasExAbilitySystemComponent;

class UGasExActionSequence;
class UGasExActionNodeBase;
class UGasExActionNodeChained;
class UGasExActionSet;

UENUM()
enum class EGasExActionSequenceState : uint8
{
	NoAction		=	0 ,	// No action currently playing, Sequence is in waiting state
	ActionInProgres	=	1,	// an Action is currently in Progress
	ActionFinished	=	9, // the Current Action just finished will go back to NoAction if no follow up action can be launched
};

/**
 *
 */
UCLASS()
class GASEX_API UGasExActionSequenceInstance : public UObject
{
	GENERATED_BODY()

public:

	void SetAbilitySystem(UGasExAbilitySystemComponent* AbilitySystem);
	
//	void SetSequence( UGasExActionSequence* Sequence);

	void AddActionSet( UGasExActionSet* Set );

	// do necessary actions when an input is Triggered
	void OnInputTriggered( FGameplayTag InputTag );

	virtual void Tick();


	// function for activation of the Cancel window
	void OnCancelWindowStart( FString WindowName );
	void OnCancelWindowEnd( FString WindowName );


	bool IsSequenceInProgress()const;

// Methods
private:

	// process the different States of the Graph instance, called from Tick function
	void ProcessWaitingState();
	void ProcessActionInProgressState();
	void ProcessActionFinishedState();

	bool TryStartSequence( UGasExActionSet* Set , FGameplayTag InputTag );
	bool TryStartSequence( UGasExActionSequence* Sequence , FGameplayTag InputTag );

	bool ExecuteAction( UGasExActionNodeBase*  NewActionNode );

	void OnAbilityEnded( const FAbilityEndedData& EndedData );

//	bool CanExecuteLinkedAction( FGameplayTag InputTag , UGasExActionNodeLink* Link );

	bool CanExecuteAction( UGasExActionNodeBase* Node , FGameplayTag InputTag );

	bool TryCancelCurrentAction( UGasExActionNodeBase* Node ,FGameplayTag InputTag );

	bool IsCancelWindowActive( FString WindowName );

private:
	// State of the Instance
	EGasExActionSequenceState				CurrentState;

	TObjectPtr<UGasExAbilitySystemComponent> AbilitySystemComponent;

	// the different action set possible to use
	TArray<TObjectPtr<UGasExActionSet>>		ActionSets;

	// the Graph instanciated
	TObjectPtr<UGasExActionSequence>		CurrntSequence;
	TObjectPtr<UGasExActionNodeBase>		CurrentNode;


	TQueue<FGameplayTag>					InputQueue;

	bool									IsCancelWindowsActive;
	TArray<FString>							CancelWindows;



};
