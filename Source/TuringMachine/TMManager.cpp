// Fill out your copyright notice in the Description page of Project Settings.


#include "TMManager.h"

void ATMManager::BeginPlay()
{
	ParseDataFromFile();
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
}
