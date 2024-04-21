// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "GasExActionEnums.generated.h"

UENUM()
enum class EGasExActionCancelWindowType
{
	Immediate ,	// cancel current Action immediatly
	Delayed		// Cancel action at the end of the Window
};
