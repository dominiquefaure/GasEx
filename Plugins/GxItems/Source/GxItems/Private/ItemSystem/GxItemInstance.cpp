// Copyright Dominique Faure. All Rights Reserved.

#include "ItemSystem/GxItemInstance.h"
#include "ItemSystem/GxItem.h"
#include "ItemSystem/GxItemInstanceTrait.h"
#include "ItemSystem/GxItemTrait.h"

//----------------------------------------------------------------------------------------------------------------
AActor* UGxItemInstance::GetOwningActor() const
{
	return Cast<AActor>( GetOuter() );
}
//----------------------------------------------------------------------------------------------------------------
void UGxItemInstance::Initialize( UGxItem* InItemDefinition )
{
	if( !InItemDefinition )
	{
		UE_LOG( LogTemp , Warning , TEXT( "UGxItemInstance::Initialize - InItemDefinition is null" ) );
		return;
	}

	// Store reference to the Item data asset
	ItemDefinition = InItemDefinition;

	for( const TInstancedStruct<FGxItemTrait>& Trait : InItemDefinition->Traits )
	{
		const UScriptStruct* TraitInstanceStruct = Trait.GetPtr()->GetInstanceScriptStruct();
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
