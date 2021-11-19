// Fill out your copyright notice in the Description page of Project Settings.


#include "TMManager.h"
#include "Tape.h"

void ATMManager::ExecuteReaction(FReactionStruct* Reaction)
{

	if(Reaction->bError)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ERROR"));
		return;
	}

	//Switching state

	if (Reaction->NewState == FinalStateSymbol)
	{
		FinishTuringMachine();
	}

	for (int i =0; i < States.Num(); ++i)
	{
		if(States[i].Name == Reaction->NewState)
		{
			CurrentState = &States[i];
			
			break;
		}
	}

	//Writing symbol
	if(Reaction->NewChar != Tape[TapePointer])
	{
		// add some effects
	}
	Tape[TapePointer] = Reaction->NewChar;
	if(TapeActor)
	{
		TapeActor->UpdateSymbolByIndex(TapePointer);
	}

	//Moving
	MoveTapePointer(Reaction->Move);
}

void ATMManager::InitializeTape()
{
	int UserTape = Tape.Num();
	FString StringToAdd(ClearSymbol);
	for (int i = 0; i < MaxTapeLength/2; ++i)
	{
		Tape.Insert(StringToAdd, 0);
	}

	int NumIterations = MaxTapeLength - Tape.Num();
	for (int i = 0; i < NumIterations; ++i)
	{
		Tape.Add(StringToAdd);
	}
}

void ATMManager::MoveTapePointer(EMoveReaction Move)
{
	if(Move == R) TapePointer++;
	if (Move == L) TapePointer--;
	
}

void ATMManager::UpdateDefaultTape()
{
}

void ATMManager::BeginPlay()
{
	ParseDataFromFile();
	InitializeTape();
	DefaultTape = Tape;
	TapeActor->GenerateTape();
	//Simulate();
}

void ATMManager::ParseDataFromFile()
{
	FFileHelper::LoadFileToStringArray(Rows, *FilePath);

	TArray<FString> StateNames;
	Rows[0].ParseIntoArray(StateNames, *CSVSeparator);
	for (auto StateName : StateNames)
	{
		States.AddDefaulted(1);
		States.Last().Name = StateName;
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, StateName);
	}


	Rows.RemoveAt(0);
	for (auto Row : Rows)
	{
		TArray<FString> RowData;
		TArray<FString> ParsedData;
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, Row);

		Row.ParseIntoArray(RowData, *CSVSeparator);
		Alphabet.Add(RowData[0]);
		RowData.RemoveAt(0);
		int StateIndex = 0;
		for (auto Data : RowData)
		{
			if (Data == ErrorSymbol)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("НУ ПИЗДЕЦ БЛЯ"));
				FReactionStruct NewReaction;
				NewReaction.bError = true;
				States[StateIndex].Reactions.Add(NewReaction);
			}
			else
			{
				Data.ParseIntoArray(ParsedData, *ReactionSeparator);
				FReactionStruct NewReaction;
				NewReaction.NewState = ParsedData[0];
				NewReaction.NewChar = ParsedData[1];
				if (ParsedData[2] == "r" && ParsedData[2] == "R")
					NewReaction.Move = EMoveReaction::R;
				if (ParsedData[2] == "l" && ParsedData[2] == "L")
					NewReaction.Move = EMoveReaction::L;
				if (ParsedData[2] == "n" && ParsedData[2] == "N")
					NewReaction.Move = EMoveReaction::N;
				States[StateIndex].Reactions.Add(NewReaction);

			}
			++StateIndex;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Emerald, TEXT("Parsing Completed"));
}

ATMManager::ATMManager()
{
	TapePointer = MaxTapeLength / 2;
	
}

void ATMManager::Simulate()
{
	TapeActionStack.Empty();

	CurrentState = &States[0];
	for(int i = 0; i < MaxSolveIterations; ++i)
	{
		if (bForceFinish) {
			bForceFinish = false;
			break;
		}

		if (Tape.IsValidIndex(TapePointer))
		{
			for (int j = 0; j < Alphabet.Num(); ++j)
			{
				CurrentSymbol = Tape[TapePointer];
				if (CurrentSymbol == Alphabet[j])
				{
					FTapeActionStruct NewTapeAction;
					NewTapeAction.StateName = CurrentState->Name;
					NewTapeAction.Reaction = CurrentState->Reactions[j];
					NewTapeAction.CurrentSymbol = CurrentSymbol;
					TapeActionStack.Add(NewTapeAction);

					ExecuteReaction(&CurrentState->Reactions[j]);
					
				}
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("SIMULATION FINISHED"));
	OnActionStackUpdated.Broadcast();
}

void ATMManager::SimulateWithTapeUpdate()
{
	Simulate();
	TapeActor->GenerateTape();
}

void ATMManager::ResetTuringMachine()
{
	Tape = DefaultTape;
	TapePointer = MaxTapeLength / 2;
	TapeActionStack.Empty();
	CurrentState = &States[0];
	TapeActor->GenerateTape();

	OnActionStackUpdated.Broadcast();
}


void ATMManager::FinishTuringMachine()
{
	bForceFinish = true;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("TURING MACHINE FINISHED EXECUTION"));
}

void ATMManager::SimulateSBS()
{
	Simulate();
	Tape = DefaultTape;
	TapeActor->GenerateTape();
}

void ATMManager::NextActionOnTapeActor()
{
	TapeActor->MoveTape(TapeActionStack[TapeActionIndex].Reaction.Move);
	TapeActionIndex++;

	//TapeActor->UpdateSymbolByIndexWithAnim();
}

void ATMManager::PreviousActionOnTapeActor()
{

}
