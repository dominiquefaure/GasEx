// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Core/Actions/GasExActionGraph.h"
#include "Core/Actions/GasExActionGraphInstance.h"


#include "GasExActionSystemComponent.generated.h"


UCLASS( ClassGroup=( GasEx ) , meta=( BlueprintSpawnableComponent ) )
class GASEX_API UGasExActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGasExActionSystemComponent();

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Action Graph")
	TObjectPtr<UGasExActionGraph> ActionGraph;


	UFUNCTION( BlueprintCallable )
	void TestFirstAction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	TObjectPtr<UGasExAbilitySystemComponent> AbilitySystem;

	TObjectPtr<UGasExActionGraphInstance> GraphInstance;

};