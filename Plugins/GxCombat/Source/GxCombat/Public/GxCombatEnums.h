// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

UENUM( BlueprintType )
enum class EGxCombatCollisionSlot : uint8
{
	LeftHandWeapon ,
	RightHandWeapon ,
	TwoHandWeapon ,
	LeftHand ,
	RightHand ,
	LeftLeg ,
	RightLeg
};

UENUM( BlueprintType )
enum class EGxCombatCollisionType : uint8
{
	Attack ,
	Block ,
	Counter
};

UENUM( BlueprintType )
enum class EGxCollisionShapeType: uint8
{
	BOX = 0 UMETA( DisplayName = "Box" ) ,
	CAPSULE UMETA( DisplayName = "Capsule" ) ,
	SPHERE UMETA( DisplayName = "Sphere" )
};