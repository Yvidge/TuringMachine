// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWEditableReaction.h"

#include "Components/EditableText.h"

bool UUWEditableReaction::IsStateCorrect(const FText State, const ATMManager* Manager)
{
	if (!Manager) return false;
	for (int i = 0; i < Manager->States.Num(); ++i)
	{
		if (Manager->States[i].Name == State.ToString()) return true;
	}
	if (State.ToString() == Manager->FinalStateSymbol) return true;
	return false;
}

bool UUWEditableReaction::IsSymbolCorrect(const FText Symbol, const ATMManager* Manager)
{
	if (!Manager) return false;
	if(Manager->Alphabet.Find(Symbol.ToString()) != INDEX_NONE) return true;
	return false;
}

bool UUWEditableReaction::IsMoveCorrect(const FText Move, const ATMManager* Manager)
{
	if (!Manager) return false;
	if (Move.ToString() == "R") return true;
	if (Move.ToString() == "r") return true;
	if (Move.ToString() == "L") return true;
	if (Move.ToString() == "l") return true;
	if (Move.ToString() == "N") return true;
	if (Move.ToString() == "n") return true;
	return false;
}

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

void UUWEditableReaction::UpdateLinkedStruct()
{
	if(LinkedReactionStruct)
	{
		LinkedReactionStruct->NewState = StateLabel->GetText().ToString();
		LinkedReactionStruct->NewChar = SymbolLabel->GetText().ToString();

		if (MoveLabel->GetText().ToString() == "R" || MoveLabel->GetText().ToString() == "r") LinkedReactionStruct->Move = R;
		else if (MoveLabel->GetText().ToString() == "L" || MoveLabel->GetText().ToString() == "l") LinkedReactionStruct->Move = L;
		else LinkedReactionStruct->Move = N;
	}
}
