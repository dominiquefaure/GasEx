// Copyright Dominique Faure. All Rights Reserved.


#include "ItemSystem/GxItemDefinition.h"
#include "ItemSystem/GxItemInstance.h"

//----------------------------------------------------------------------------------------------------------------
FGxItemDefinition::FGxItemDefinition()
{
	// Default constructor
	InstanceType = UGxItemInstance::StaticClass();
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
TSubclassOf<UGxItemInstance> FGxItemDefinition::GetInstanceClass() const
{
	return InstanceType;
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
UGxItemInstance* FGxItemDefinition::CreateInstance( UObject* Outer ) const
{
	UGxItemInstance* NewInstance = nullptr;
	if( InstanceType == nullptr)
	{
		UE_LOG( LogTemp , Warning , TEXT( "InstanceType is null in ItemDefinition" ) );
		return nullptr;
	}
	NewInstance	=	NewObject<UGxItemInstance>( Outer , InstanceType );

//	NewInstance->Initialize( TInstancedStruct<FGxItemDefinition>( *this ) );
	NewInstance->Initialize( *this );

	return NewInstance;
}
//----------------------------------------------------------------------------------------------------------------

