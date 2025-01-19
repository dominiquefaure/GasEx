// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "HitDetection/GxHitDetectionSettings.h"
#include "Misc/App.h"

//#include UE_INLINE_GENERATED_CPP_BY_NAME(UGxHitDetectionSettings)

//-----------------------------------------------------------------------------------------
UGxHitDetectionSettings::UGxHitDetectionSettings()
{
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FName UGxHitDetectionSettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}
//-----------------------------------------------------------------------------------------
