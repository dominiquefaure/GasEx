// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "GxCombatComponent.h"
#include "Components/ShapeComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "Math/RotationMatrix.h"

#include "GxAbilitySystemComponent.h"
#include "Abilities/GxGameplayAbility.h"
#include "Attacks/GxAttackMoveSet.h"
#include "GxHitComponent.h"
#include "HitDetection/GxHitDetectionDebugDraw.h"


UE_DEFINE_GAMEPLAY_TAG( TAG_Event_Combat_Hit , "GxCombat.Event.CollisionHit" )


//-----------------------------------------------------------------------------------------
// Sets default values for this component's properties
UGxCombatComponent::UGxCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bAttackWindowActive=true;
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
// Called when the game starts
void UGxCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	AbilitySystemComponent	=	GetOwner()->GetComponentByClass<UGxAbilitySystemComponent>();

	RegisterMoves( "Default" , DefaultMoveset );
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
// Called every frame
void UGxCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	TArray<FHitResult> Results;
	for( FGxHitWindow& Element : HitWindows )
	{
		Element.PerformHitDetection( Results );
	}

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxCombatComponent::RegisterHitComponent( EGxCollisionSource InSource , UGxHitComponent* InComponent )
{
	FGxInitiatorCollisionComponent NewComponent;
	NewComponent.CollisionSource	=	InSource;
	NewComponent.HitComponent		=	InComponent;
	HitComponents.Add( NewComponent );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxCombatComponent::UnRegisterHitComponent( EGxCollisionSource InSource )
{

}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
void UGxCombatComponent::StartCollisionDetection( EGxCollisionSource InSource , const FString& InHitComponentFilter )
{
	FGxHitWindow HitWindow;

	HitWindow.Source	=	InSource;

	for( FGxInitiatorCollisionComponent& Element : HitComponents )
	{
		if( Element.CollisionSource == InSource )
		{
			for( UGxHitDetectionBase* HitCollisionElement : Element.HitComponent->HitCollisionElements )
			{
				HitWindow.HitElements.Add( HitCollisionElement );

			}
				//Element.HitComponent->SetHitDetectionEnable( true );
		}
	}
	HitWindows.Add( HitWindow );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxCombatComponent::EndCollisionDetection( EGxCollisionSource InSource , const FString& InHitComponentFilter )
{
	int Index	=	0;
	while( Index < HitWindows.Num() )
	{
		if( HitWindows[Index].Source == InSource )
		{
			HitWindows.RemoveAt( Index );
		}
		else
		{
			Index++;
		}
	}

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxCombatComponent::RegisterMoves( FString InName , UDataTable* InTable )
{
	UGxAttackMoveSet* NewMoveSet	=	NewObject< UGxAttackMoveSet>();

	NewMoveSet->Register( InName , InTable , AbilitySystemComponent );

	MoveSets.Add( NewMoveSet );
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
bool UGxCombatComponent::TryExecuteAttack( FGameplayTag InAttackTag )
{
	TObjectPtr<UGxAttackAction> Attack	=	GetCombatAttack( InAttackTag );

	if( Attack != nullptr )
	{
		return AbilitySystemComponent->TryActivateAbility( Attack->AbilitySpec.Handle );
	}

	return false;
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
TObjectPtr<UGxAttackAction> UGxCombatComponent::GetCombatAttack( FGameplayTag InTag )
{
	UGxAttackAction* Attack;
	for( UGxAttackMoveSet* MoveSet : MoveSets )
	{
		Attack	=	MoveSet->GetCombatAttack( InTag );

		if( Attack != nullptr )
		{
			return Attack;
		}
	}
	return nullptr;
}
//-----------------------------------------------------------------------------------------
