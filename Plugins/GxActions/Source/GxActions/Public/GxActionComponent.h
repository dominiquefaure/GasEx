// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GxActionContext.h"
#include "GxActionComponent.generated.h"

class UGxAbilitySystemComponent;
class UGxActionGraph;
class UGxActionGraphInstance;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GXACTIONS_API UGxActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGxActionComponent();


	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Action Graph")
	TObjectPtr<UGxActionGraph> ActionGraph;


	UFUNCTION( BlueprintCallable )
	void OnInputTriggered( FGameplayTag InputTag );

	// function for activation of the Cancel window
	void OnCancelWindowStart( FString WindowName );
	void OnCancelWindowEnd( FString WindowName );

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnUnregister() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	
	void OnAbilityEnded( const FAbilityEndedData& EndedData );

	// process the different States of an Action , called from Tick function
	void ProcessWaitingState( );
	void ProcessInProgressState();
	void ProcessFinishedState();

	/*
	* Stop the current action and reset the state to the waiting state
	* 
	*/
	void ResetActions();

private:

	UPROPERTY( Transient )
	TObjectPtr<UGxAbilitySystemComponent>	AbilitySystemComponent;

	// execution Context
	UPROPERTY( Transient )
	FGxActionContext						ExecutionContext;



	UPROPERTY()// declare uproperty to avoid the object beeing GC
	TObjectPtr<UGxActionGraphInstance> GraphInstance;

};
