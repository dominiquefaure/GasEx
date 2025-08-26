
#include "Equipment/GxEquipmentManagerComponent.h"
#include "ItemSystem/GxItemInstance.h"
#include "Equipment/GxItemInstanceTrait_Equipment.h"
#include "Equipment/GxItemTrait_Equipment.h"


//-----------------------------------------------------------------------------------------
UGxEquipmentManagerComponent::UGxEquipmentManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // Set to false if you don't need to tick this component every frame
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxEquipmentManagerComponent::EquipItem( UGxItemInstance* ItemInstance )
{
	if( ItemInstance == nullptr )
	{
		return false;
	}

	FGxItemInstanceTrait_Equipment* EquipmentTrait	=	ItemInstance->GetTrait<FGxItemInstanceTrait_Equipment>();
	if( EquipmentTrait == nullptr )
	{
		UE_LOG( LogTemp , Warning , TEXT( "ItemInstance does not have an Equipment trait." ) );
		return false;
	}

	EquipmentTrait->OnEquip();


	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxEquipmentManagerComponent::UnequipItem( UGxItemInstance* ItemInstance )
{
}
//-----------------------------------------------------------------------------------------
