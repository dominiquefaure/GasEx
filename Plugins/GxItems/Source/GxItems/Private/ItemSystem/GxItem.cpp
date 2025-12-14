// Copyright Dominique Faure. All Rights Reserved.

#include "ItemSystem/GxItem.h"
#include "ItemSystem/GxItemInstance.h"

//----------------------------------------------------------------------------------------------------------------
UGxItem::UGxItem()
{
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
TSubclassOf<UGxItemInstance> UGxItem::GetInstanceClass() const
{
	return UGxItemInstance::StaticClass();
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
UGxItemInstance* UGxItem::CreateInstance( UObject* Outer )
{
	UGxItemInstance* NewInstance = nullptr;

	UClass* InstanceType = GetInstanceClass();

	if( InstanceType == nullptr)
	{
		UE_LOG( LogTemp , Warning , TEXT( "InstanceType is null in GxItem" ) );
		return nullptr;
	}
	NewInstance	=	NewObject<UGxItemInstance>( Outer , InstanceType );

	NewInstance->Initialize( this );

	return NewInstance;
}
//----------------------------------------------------------------------------------------------------------------

