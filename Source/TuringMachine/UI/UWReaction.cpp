// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWReaction.h"

#include "Components/TextBlock.h"

void UUWReaction::InitializeFromData(const FReactionStruct Reaction)
{
	if (Reaction.bError)
	{
		StateLabel->SetText(FText::FromString(""));
		SymbolLabel->SetText(FText::FromString("ERR"));
		MoveLabel->SetText(FText::FromString(""));
	}
	else
	{
		StateLabel->SetText(FText::FromString(Reaction.NewState));
		SymbolLabel->SetText(FText::FromString(Reaction.NewChar));
		FText MoveText;
		if (Reaction.Move == R) MoveText = FText::FromString("R");
		if (Reaction.Move == L) MoveText = FText::FromString("L");
		if (Reaction.Move == N) MoveText = FText::FromString("N");
		MoveLabel->SetText(MoveText);
	}


}
