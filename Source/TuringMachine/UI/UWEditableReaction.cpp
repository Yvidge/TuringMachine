// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWEditableReaction.h"

#include "Components/EditableText.h"

void UUWEditableReaction::InitializeFromData()
{
	if (LinkedReactionStruct)
	{
		if (LinkedReactionStruct->bError)
		{
			//StateLabel->SetText(FText::FromString(""));
			StateLabel->SetText(FText::FromString(""));
			SymbolLabel->SetText(FText::FromString("ERR"));
			MoveLabel->SetText(FText::FromString(""));
		}
		else
		{
			StateLabel->SetText(FText::FromString(LinkedReactionStruct->NewState));
			SymbolLabel->SetText(FText::FromString(LinkedReactionStruct->NewChar));
			FText MoveText;
			if (LinkedReactionStruct->Move == R) MoveText = FText::FromString("R");
			if (LinkedReactionStruct->Move == L) MoveText = FText::FromString("L");
			if (LinkedReactionStruct->Move == N) MoveText = FText::FromString("N");
			MoveLabel->SetText(MoveText);
		}

	}
}
