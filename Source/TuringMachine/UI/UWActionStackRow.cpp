// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWActionStackRow.h"

#include "UWReaction.h"
#include "UWSymbol.h"
#include "Components/TextBlock.h"

void UUWActionStackRow::InitializeFromData(const FTapeActionStruct& Action)
{
	StateLabel->SetText(FText::FromString(Action.StateName));
	ReactionLabel->InitializeFromData(Action.Reaction);
	CurrentSymbolLabel->SetText(FText::FromString(Action.CurrentSymbol));
}
