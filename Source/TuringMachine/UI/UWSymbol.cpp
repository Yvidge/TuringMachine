// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWSymbol.h"

#include "Components/TextBlock.h"

void UUWSymbol::SetText(FText Text)
{
	SymbolLabel->SetText(Text);
}

FText UUWSymbol::GetText()
{
	return SymbolLabel->GetText();
}
