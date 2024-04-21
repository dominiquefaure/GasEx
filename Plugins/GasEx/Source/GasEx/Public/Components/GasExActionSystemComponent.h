// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Core/Actions/GasExActionGraph.h"
#include "Core/Actions/GasExActionGraphInstance.h"

#include "Core/Actions/GasExActionInputConfig.h"

#include "GasExActionSystemComponent.generated.h"


UCLASS( ClassGroup=( GasEx ) , meta=( BlueprintSpawnableComponent ) )
class GASEX_API UGasExActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGasExActionSystemComponent();

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Action Graph" )
	TObjectPtr<UGasExInputConfig> InputConfig;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Action Graph")
	TObjectPtr<UGasExActionGraph> ActionGraph;

	UFUNCTION( BlueprintCallable )
	void RegisterInputs( UInputComponent* PlayerInputComponent );

	// function for activation of the Cancel window
	void OnCancelWindowStart( FString WindowName );
	void OnCancelWindowEnd( FString WindowName );

private:

	void OnInputTriggered( FGameplayTag InputTag );

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnUnregister() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	TObjectPtr<UGasExAbilitySystemComponent> AbilitySystem;

	TObjectPtr<UGasExActionGraphInstance> GraphInstance;

};
