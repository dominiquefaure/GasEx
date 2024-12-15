// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GxCombatEnums.h"
#include "NativeGameplayTags.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "GxCombatComponent.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN( TAG_Event_Combat_Hit )


USTRUCT( BlueprintType )
struct FGxCombatCollisionShape
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly , Category = "Shape" , meta = ( DisplayName = "Type of Shape to use for Collision" ) )
	EGxCollisionShapeType ShapeType;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Shape" , meta = ( DisplayName = "Box Half Extent" , EditCondition = "ShapeType == EGxCollisionShapeType::BOX" , EditConditionHides ) )
	FVector BoxHalfExtend	=	FVector( 50 , 50 , 50 );

	// Capsule shape values
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Shape" , meta = ( DisplayName = "Capsule Half Height" , EditCondition = "ShapeType == EGxCollisionShapeType::CAPSULE" , EditConditionHides ) )
	float CapsuleHalfHeight	=	50;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Shape" , meta = ( DisplayName = "Capsule Radius" , EditCondition = "ShapeType == EGxCollisionShapeType::CAPSULE" , EditConditionHides ) )
	float CapsuleRadius	=	10;

	// Sphere values
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Shape" , meta = ( DisplayName = "Sphere Radius" , EditCondition = "ShapeType == EGxCollisionShapeType::SPHERE" , EditConditionHides ) )
	float SphereRadius	=	10;
};


USTRUCT( BlueprintType )
struct FGxCombatCollision
{
	GENERATED_BODY()

	EGxCombatCollisionType CollisionType;
	EGxCombatCollisionSlot CollisionSlot;
	UShapeComponent* ShapeComponent;


	UPROPERTY( BlueprintReadOnly , Category = "Collision" , meta = ( DisplayName = "Scene Component To Sync for position and Transform" ) )
	TObjectPtr<USceneComponent>	SyncComponent;

	UPROPERTY( BlueprintReadOnly , Category = "Collision" , meta = ( DisplayName = "Offset from the Scene Component, absolute position if no Sync component" ) )
	FTransform Offset  = FTransform::Identity;


	UPROPERTY( BlueprintReadOnly , Category = "Shape" , meta = ( DisplayName = "The Shape to use for Collision" ) )
	FGxCombatCollisionShape Shape;

	FTransform PreviousTransform;
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void CollisionOverlap( UPrimitiveComponent* OverlappedComp , AActor* Other , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION( BlueprintCallable )
	void AddCollisionShapeComponent( UShapeComponent* Shape , EGxCombatCollisionSlot Slot , EGxCombatCollisionType Type );


	UPROPERTY()
	TArray<FGxCombatCollision> CollisionShapes;

	bool bAttackWindowActive;


private:

	void EvaluateCollisions( FGxCombatCollision& CollisionShape );

	void EvaluateCollisions( const FVector& Start , const FVector& End , const FGxCombatCollisionShape& CollisionShape );


};
