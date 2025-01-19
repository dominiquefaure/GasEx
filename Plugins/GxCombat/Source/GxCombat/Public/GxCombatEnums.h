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

