// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWSymbol.h"

#include "Components/TextBlock.h"
#include "Components/EditableText.h"

void UUWSymbol::SetText(FText Text)
{
	SymbolLabel->SetText(Text);
	PreviousSymbol = Text.ToString();
}

FText UUWSymbol::GetText()
{
	return SymbolLabel->GetText();
}

void UUWSymbol::UpdateSymbolInAlphabet(const FString NewSymbol, ATMManager* Manager)
{
	if(Manager)
	{
		int Index = Manager->Alphabet.Find(PreviousSymbol);
		Manager->Alphabet[Index] = NewSymbol;
		PreviousSymbol = NewSymbol;
	}
}

bool UUWSymbol::CheckIsNewSymbolUnique(const FString NewSymbol, const ATMManager* Manager)
{
	if (!Manager) return false;
	return !Manager->Alphabet.Contains(NewSymbol);
}
