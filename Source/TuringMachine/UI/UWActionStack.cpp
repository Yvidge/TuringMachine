// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWActionStack.h"

#include "UWActionStackRow.h"
#include "Components/ScrollBox.h"

void UUWActionStack::InitializeFromData(const TArray<FTapeActionStruct>& Actions)
{
	CreatedRows.Empty();
	MainPanel->ClearChildren();

	for (FTapeActionStruct Action : Actions)
	{

		UUWActionStackRow* CreatedRow = CreateWidget<UUWActionStackRow>(this, ActionRowClass);
		CreatedRow->InitializeFromData(Action);
		MainPanel->AddChild(CreatedRow);
		CreatedRows.Add(CreatedRow);
	}

}

void UUWActionStack::SetHighlightedAction(int Index)
{
	for (UUWActionStackRow* Row : CreatedRows)
	{
		Row->SetHighlighting(false);
	}

	CreatedRows[Index]->SetHighlighting(true);
}
