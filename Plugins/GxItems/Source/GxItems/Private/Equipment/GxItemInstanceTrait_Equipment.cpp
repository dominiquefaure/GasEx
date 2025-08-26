

#include "Equipment/GxItemInstanceTrait_Equipment.h"
#include "Equipment/GxItemTrait_Equipment.h"


#include "ItemSystem/GxItemInstance.h"

//----------------------------------------------------------------------------------------------------------------
APawn* FGxItemInstanceTrait_Equipment::GetOwnerPawn() const
{
	return Cast<APawn>( OwnerItem->GetOwningActor() );
}
//----------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
void FGxItemInstanceTrait_Equipment::OnEquip()
{
	if( bIsEquipped )
	{
		UE_LOG( LogTemp , Warning , TEXT( "UGxItemInstance - Try to Equip an Item that is already equiped %s" ) , *OwnerItem->GetName() );

		return;
	}

	const FGxItemTrait_Equipment* EquipmentTrait = TraitDefinition.GetPtr<FGxItemTrait_Equipment>();
	if( EquipmentTrait == nullptr )
	{
		UE_LOG( LogTemp , Error  , TEXT( "UGxItemInstance - Failed to get Equipment Trait for Item %s" ) , *OwnerItem->GetName() );
		return;
	}

	APawn* OwnerPawn = GetOwnerPawn();
	if( OwnerPawn == nullptr )
	{
		UE_LOG( LogTemp , Error , TEXT( "UGxItemInstance - Failed to get Owner Pawn for Item %s" ) , *OwnerItem->GetName() );
		return;
	}


	for(const FEquipmentActorToSpawn& ActoToSpawn : EquipmentTrait->ActorsToSpawn )
	{
		if( ActoToSpawn.ActorClass == nullptr )
		{
			UE_LOG( LogTemp , Warning , TEXT( "UGxItemInstance - Actor Class is null for Item %s" ) , *OwnerItem->GetName() );
			continue;
		}

		if( ActoToSpawn.AttachSocket.IsNone() )
		{
			UE_LOG( LogTemp , Warning , TEXT( "UGxItemInstance - Attach Socket is empty for Item %s" ) , *OwnerItem->GetName() );
			continue;
		}

		AActor* NewActor = OwnerPawn->GetWorld()->SpawnActorDeferred<AActor>( ActoToSpawn.ActorClass , FTransform::Identity , OwnerPawn );
		if( NewActor )
		{
			NewActor->FinishSpawning( FTransform::Identity , /*bIsDefaultTransform=*/ true );
			NewActor->SetActorRelativeTransform( ActoToSpawn.AttachTransform );
			NewActor->AttachToComponent( OwnerPawn->GetRootComponent() , FAttachmentTransformRules::KeepRelativeTransform , ActoToSpawn.AttachSocket );
			SpawnedActors.Add( NewActor );
		}
	}

	bIsEquipped = true;
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
void FGxItemInstanceTrait_Equipment::OnUnEquip()
{
	// Destroy the different spawned actors
	for (AActor* Actor : SpawnedActors)
	{
		if (Actor)
		{
			Actor->Destroy();
		}
	}

	bIsEquipped = false;
}
//----------------------------------------------------------------------------------------------------------------
