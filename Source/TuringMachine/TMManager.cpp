// Fill out your copyright notice in the Description page of Project Settings.


#include "TMManager.h"


#include "Tape.h"
#include "Misc/FileHelper.h"

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
	if (Move == R) TapePointer++;
	if (Move == L) TapePointer--;
	
}

void ATMManager::UpdateDefaultTape()
{
	DefaultTape = Tape;
}

void ATMManager::BeginPlay()
{
	//ParseDataFromFile();
	InitializeTape();
	DefaultTape = Tape;
	TapeActor->GenerateTape();
	//Simulate();
}

EMoveReaction ATMManager::RevertMove(EMoveReaction Move)
{
	if (Move == R) return L;
	if (Move == L) return R;
	return N;
}

void ATMManager::ParseDataFromFile()
{
	States.Empty();
	Alphabet.Empty();
	Rows.Empty();


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
				//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("НУ ПИЗДЕЦ БЛЯ"));
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
	OnNewTuringMachineLoaded.Broadcast();
}

ATMManager::ATMManager()
{
	TapePointer = MaxTapeLength / 2;
	
}

void ATMManager::Simulate()
{
	if (!bCorrectTape) return;

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
	if (!bCorrectTape) return;
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
	if (!bCorrectTape) return;

	Simulate();
	Tape = DefaultTape;
	TapeActor->GenerateTape();
	TapeActionIndex = 0;
	TapePointer = MaxTapeLength / 2;
	OnCurrentActionUpdated.Broadcast(TapeActionIndex);
}

void ATMManager::NextActionOnTapeActor()
{
	//TapeActor->UpdateSymbolByIndex(TapeActionIndex);
	if (TapeActionIndex != TapeActionStack.Num()-1) {
		if (TapeActor->GetSymbolByIndex(TapePointer) != TapeActionStack[TapeActionIndex].Reaction.NewChar)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("%s != %s"), *TapeActor->GetSymbolByIndex(TapePointer), *TapeActionStack[TapeActionIndex].Reaction.NewChar));
			TapeActor->SetSymbolByIndex(TapePointer, TapeActionStack[TapeActionIndex].Reaction.NewChar);
			TapeActor->PlayHeadAnim();
			GetWorldTimerManager().SetTimer(WritingTimer, this, &ATMManager::NextActionSymbolAnimEnded, TapeActor->SymbolUpdateDuration, false);
		}
		else
		{
			NextActionSymbolAnimEnded();
		}
		MoveTapePointer(TapeActionStack[TapeActionIndex].Reaction.Move);
	}
	
	//TapeActor->UpdateSymbolByIndexWithAnim();
}

void ATMManager::NextActionSymbolAnimEnded()
{
	TapeActor->MoveTape(TapeActionStack[TapeActionIndex].Reaction.Move);
	TapeActionIndex++;
	OnCurrentActionUpdated.Broadcast(TapeActionIndex);
}

void ATMManager::PreviousActionSymbolAnimEnded()
{
	if (TapeActionStack[TapeActionIndex - 1].Reaction.NewChar != TapeActionStack[TapeActionIndex - 1].CurrentSymbol) {
		TapeActor->SetSymbolByIndex(TapePointer, TapeActionStack[TapeActionIndex - 1].CurrentSymbol);
		TapeActor->PlayHeadAnim();
	}
	TapeActionIndex--;

	OnCurrentActionUpdated.Broadcast(TapeActionIndex);
}

void ATMManager::PreviousActionOnTapeActor()
{
	if(TapeActionIndex != 0)
	{
		TapeActor->MoveTape(RevertMove(TapeActionStack[TapeActionIndex - 1].Reaction.Move));
		MoveTapePointer(RevertMove(TapeActionStack[TapeActionIndex - 1].Reaction.Move));

		GetWorldTimerManager().SetTimer(WritingTimer, this, &ATMManager::PreviousActionSymbolAnimEnded, TapeActor->SymbolUpdateDuration, false);

		
	}
}

void ATMManager::LoadTMFromFile()
{

}

void ATMManager::UpdateTapeSymbolByIndex(int Index, FString NewSymbol)
{
	if(Tape.IsValidIndex(Index))
	{
		Tape[Index] = NewSymbol;
		UpdateDefaultTape();
	}
}

void ATMManager::AddNewState()
{
	FStateStruct NewState;
	FString Name("q");
	Name.Append(FString::FromInt(FMath::Rand() % 100));
	NewState.Name = Name;//TEXT("Q");
	for (int i = 0; i < Alphabet.Num(); ++i)
	{
		FReactionStruct NewReaction;
		NewState.Reactions.Add(NewReaction);
	}
	States.Add(NewState);
	OnNewTuringMachineLoaded.Broadcast(); //Recreating widget
}

void ATMManager::AddNewSymbolToAlphabet()
{
	FString NewSymbol = Alphabet.Last();
	Alphabet.Add(NewSymbol.AppendChar('1'));
	for (int i = 0; i < States.Num(); ++i)
	{
		FStateStruct* State = &States[i];
		FReactionStruct NewReaction;
		State->Reactions.Add(NewReaction);

		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("BRUH"));
		//States[i].Name = "P";
		//State->Name = "P";
	}
	OnNewTuringMachineLoaded.Broadcast(); //Recreating widget
}
