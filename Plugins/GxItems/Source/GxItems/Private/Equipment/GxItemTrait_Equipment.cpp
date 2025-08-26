// Copyright Dominique Faure. All Rights Reserved.

#include "Equipment/GxItemTrait_Equipment.h"
#include "Equipment/GxItemInstanceTrait_Equipment.h"

//----------------------------------------------------------------------------------------------------------------
const UScriptStruct* FGxItemTrait_Equipment::GetInstanceScriptStruct() const
{
	return FGxItemInstanceTrait_Equipment::StaticStruct();
}
//----------------------------------------------------------------------------------------------------------------
