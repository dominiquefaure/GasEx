// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GxCombatEnums.h"
#include "NativeGameplayTags.h"
#include "HitDetection/GxHitDetectionStructs.h"
#include "HitDetection/GxHitWindow.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "GxCombatComponent.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN( TAG_Event_Combat_Hit )

class UGxAbilitySystemComponent;
class UGxHitComponent;
class UGxAttackMoveSet;
class UGxAttackAction;

USTRUCT( BlueprintType )
struct FGxInitiatorCollisionComponent
{
	GENERATED_BODY()

	/*Used to identify witch component to use : Body, Weapons....*/
	UPROPERTY(Transient)
	EGxCollisionSource CollisionSource;

	/*The hit component to use*/
	UPROPERTY( Transient )
	TObjectPtr<UGxHitComponent> HitComponent;

};

USTRUCT( BlueprintType )
struct FGxCombatHitResult :public FGameplayAbilityTargetData
{
	GENERATED_BODY()

	AActor* OtherActor;
};


UCLASS( ClassGroup=(Gx), meta=(BlueprintSpawnableComponent) )
class GXCOMBAT_API UGxCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGxCombatComponent();

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta=( RowType ="GxAction/Attacks/AttackDataRow" ) )
	TObjectPtr<UDataTable> DefaultMoveset;

public:

	UFUNCTION(BlueprintCallable)
	void RegisterHitComponent( EGxCollisionSource InSource, UGxHitComponent* InComponent );

	UFUNCTION( BlueprintCallable )
	void UnRegisterHitComponent( EGxCollisionSource InSource );

	UFUNCTION( BlueprintCallable )
	void StartCollisionDetection( EGxCollisionSource InSource ,const FString& InFilter );
	
	UFUNCTION( BlueprintCallable )
	void EndCollisionDetection( EGxCollisionSource InSource , const FString& InFilter );


	/* Try to launch an attack with the given tag*/
	UFUNCTION( BlueprintCallable )
	bool TryExecuteAttack( FGameplayTag InAttackTag );

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	void RegisterMoves( FString InName ,UDataTable* InTable );


	TObjectPtr<UGxAttackAction> GetCombatAttack( FGameplayTag InTag );

private:

	UPROPERTY( Transient )
	TObjectPtr<UGxAbilitySystemComponent> AbilitySystemComponent;


	UPROPERTY( Transient )
	TArray<FGxInitiatorCollisionComponent> HitComponents;

	UPROPERTY( Transient )
	TArray<FGxHitWindow> HitWindows;

	UPROPERTY( Transient )
	TArray< TObjectPtr<UGxAttackMoveSet>> MoveSets;

	bool bAttackWindowActive;

};
