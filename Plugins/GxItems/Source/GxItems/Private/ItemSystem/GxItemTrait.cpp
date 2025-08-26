// Copyright Dominique Faure. All Rights Reserved.

#include "ItemSystem/GxItemTrait.h"
#include "ItemSystem/GxItemInstanceTrait.h"


const UScriptStruct* FGxItemTrait::GetInstanceScriptStruct() const
{
	return FGxItemInstanceTrait::StaticStruct();
}
