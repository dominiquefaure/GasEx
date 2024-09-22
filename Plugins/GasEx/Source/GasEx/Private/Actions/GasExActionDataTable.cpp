// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Actions/GasExActionDataTable.h"


//---------------------------------------------------------------------------------------------
FGasExActionSequenceRow::FGasExActionSequenceRow()
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExActionDataTable::UGasExActionDataTable()
{
	RowStruct = FGasExActionSequenceRow::StaticStruct();
}
//---------------------------------------------------------------------------------------------
