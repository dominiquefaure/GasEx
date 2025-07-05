// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverSimulationTypes.h"

#include "GxMoverInputProducerComponent.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GXMOVEMENT_API UGxMoverInputProducerComponent : public UActorComponent , public IMoverInputProducerInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGxMoverInputProducerComponent();



	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> MoveInputAction;
   
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> LookInputAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> JumpInputAction;

	/** Fly Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> FlyInputAction;


	// Whether or not we author our movement inputs relative to whatever base we're standing on, or leave them in world space. Only applies if standing on a base of some sort.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MoveOrientation)
	bool bUseBaseRelativeMovement = true;
	
	/**
	 * If true, rotate the Character toward the direction the actor is moving
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MoveOrientation)
	bool bOrientRotationToMovement = true;
	
	/**
	 * If true, the actor will continue orienting towards the last intended orientation (from input) even after movement intent input has ceased.
	 * This makes the character finish orienting after a quick stick flick from the player.  If false, character will not turn without input.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveOrientation)
	bool bMaintainLastInputOrientation = false;





protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// IMoverInputProducerInterface
	// Entry point for input production. Do not override. To extend in derived character types, override OnProduceInput for native types or implement "Produce Input" blueprint event
	virtual void ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult) override;
	//end IMoverInputProducerInterface

	// Override this function in native class to author input for the next simulation frame. Consider also calling Super method.
	virtual void OnProduceInput(float DeltaMs, FMoverInputCmdContext& InputCmdResult);



private:		
	void RegisterInputs();


// Move Actions
private:
	void OnMoveTriggered(const FInputActionValue& Value);
	void OnMoveCompleted(const FInputActionValue& Value);
	void OnLookTriggered(const FInputActionValue& Value);
	void OnLookCompleted(const FInputActionValue& Value);
	void OnJumpStarted(const FInputActionValue& Value);
	void OnJumpReleased(const FInputActionValue& Value);
	void OnFlyTriggered(const FInputActionValue& Value);


	void ProduceMoveInput( float DeltaMs , FCharacterDefaultInputs& CharacterInputs );

private:
	FVector LastAffirmativeMoveInput	=	FVector::ZeroVector;	// Movement input (intent or velocity) the last time we had one that wasn't zero
	FVector CachedMoveInputIntent		=	FVector::ZeroVector;
	FVector CachedMoveInputVelocity		=	FVector::ZeroVector;


	FRotator CachedTurnInput			=	FRotator::ZeroRotator;
	FRotator CachedLookInput			=	FRotator::ZeroRotator;

	bool bIsJumpJustPressed				=	false;
	bool bIsJumpPressed					=	false;
	bool bIsFlyingActive				=	false;
	bool bShouldToggleFlying			=	false;

	// is it using Mover or CMC
	bool bUseMover						=	false;

};
