// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "GxActionInputBuffer.h"


//---------------------------------------------------------------------------------------------
bool FGxActionInputBuffer::IsEmpty() const
{
	return InputBuffer.Num() == 0;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
const FGameplayTag FGxActionInputBuffer::GetInputTag( bool InConsume )
{
	if( InputBuffer.Num() == 0 )
	{
		return FGameplayTag::EmptyTag;
	}

	FGameplayTag InputTag = InputBuffer[0];
	if( InConsume )
	{
		InputBuffer.RemoveAt( 0 );
	}
	return InputTag;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxActionInputBuffer::OnKeyPressed( FGameplayTag InputKey )
{
	InputBuffer.Add( InputKey );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxActionInputBuffer::ClearInputs()
{
	InputBuffer.Empty();
}
//---------------------------------------------------------------------------------------------
