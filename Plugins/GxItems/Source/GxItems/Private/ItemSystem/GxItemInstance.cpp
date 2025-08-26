// Copyright Dominique Faure. All Rights Reserved.

#include "ItemSystem/GxItemInstance.h"
#include "ItemSystem/GxItemDefinition.h"
#include "ItemSystem/GxItemInstanceTrait.h"
#include "ItemSystem/GxItemTrait.h"


//----------------------------------------------------------------------------------------------------------------
AActor* UGxItemInstance::GetOwningActor() const
{
	return Cast<AActor>( GetOuter() );
}
//----------------------------------------------------------------------------------------------------------------

/*
//----------------------------------------------------------------------------------------------------------------
void UGxItemInstance::Initialize( const TInstancedStruct<FGxItemDefinition>& InItemDefinition )
{
	// Store a reference to the Item definition
	ItemDefinition = InItemDefinition;

	// Get Pointer to th Actual Item definition
	const FGxItemDefinition* ItemInstancePtr	=	InItemDefinition.GetPtr();
	for( const TInstancedStruct<FGxItemTrait>& Trait : ItemInstancePtr->Traits )
	{
		const UScriptStruct* TraitInstanceStruct=	Trait.GetPtr()->GetInstanceScriptStruct();
		if( TraitInstanceStruct != nullptr )
		{
			// create the instance of the Trait with the requested struct
			FInstancedStruct InstanceTrait;
			InstanceTrait.InitializeAs( TraitInstanceStruct );

			// Initialize the InstanceTrait with the Trait data
			FGxItemInstanceTrait* InstanceTraitPtr = InstanceTrait.GetMutablePtr<FGxItemInstanceTrait>();
			if( InstanceTraitPtr != nullptr )
			{
				InstanceTraitPtr->Initialize( Trait );

				InstanceTraitPtr->OwnerItem = this;
				ItemTraits.Add( InstanceTrait );
			}
			else
			{
				UE_LOG( LogTemp , Warning , TEXT( "UGxItemInstance::Initialize - Failed to initialize Trait Instance for %s" ) , *TraitInstanceStruct->GetName() );
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------
*/
//----------------------------------------------------------------------------------------------------------------
void UGxItemInstance::Initialize( const FGxItemDefinition& InItemDefinition )
{
	// Store a reference to the Item definition
	ItemDefinition.InitializeAs( InItemDefinition );

	for( const TInstancedStruct<FGxItemTrait>& Trait : InItemDefinition.Traits )
	{
		const UScriptStruct* TraitInstanceStruct=	Trait.GetPtr()->GetInstanceScriptStruct();
		if( TraitInstanceStruct != nullptr )
		{
			// create the instance of the Trait with the requested struct
			FInstancedStruct InstanceTrait;
			InstanceTrait.InitializeAs( TraitInstanceStruct );

			// Initialize the InstanceTrait with the Trait data
			FGxItemInstanceTrait* InstanceTraitPtr = InstanceTrait.GetMutablePtr<FGxItemInstanceTrait>();
			if( InstanceTraitPtr != nullptr )
			{
				InstanceTraitPtr->Initialize( Trait );

				InstanceTraitPtr->OwnerItem = this;
				ItemTraits.Add( InstanceTrait );
			}
			else
			{
				UE_LOG( LogTemp , Warning , TEXT( "UGxItemInstance::Initialize - Failed to initialize Trait Instance for %s" ) , *TraitInstanceStruct->GetName() );
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------
