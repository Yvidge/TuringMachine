// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWTuringMachine.h"

#include "UWButton.h"
#include "UWState.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UUWTuringMachine::InitializeFromData()
{

	StateWidgets.Empty();
	SymbolPanel->ClearChildren();
	StatePanel->ClearChildren();

	if(Manager)
	{
		
		for (int i = 0; i < Manager->States.Num(); ++i)
		{
			UUWState* CreatedState = CreateWidget<UUWState>(this, StateWidgetClass);
			CreatedState->LinkedStateStruct = &(Manager->States[i]);
			StateWidgets.Add(CreatedState);
			CreatedState->InitializeFromData();
			StatePanel->AddChildToHorizontalBox(CreatedState);
		}

		NewStateButton->RemoveFromParent();
		NewStateButton = CreateWidget<UUWButton>(this, ButtonWidgetClass);
		StatePanel->AddChildToHorizontalBox(NewStateButton);
		
		//SymbolPanel->AddChildToVerticalBox(CreateWidget<UUWButton>(this, ButtonWidgetClass));

		for (FString Symbol : Manager->Alphabet)
		{
			UUWSymbol* CreatedSymbol = CreateWidget<UUWSymbol>(this, SymbolWidgetClass);
			//UTextBlock* CreatedSymbol = CreateWidget<UTextBlock>(this, UTextBlock::StaticClass());
			CreatedSymbol->SetText(FText::FromString(Symbol));
			SymbolPanel->AddChildToVerticalBox(CreatedSymbol);
			
		}

		NewSymbolButton->RemoveFromParent();
		NewSymbolButton = CreateWidget<UUWButton>(this, ButtonWidgetClass);
		SymbolPanel->AddChildToVerticalBox(NewSymbolButton);
	}

	
}

void UUWTuringMachine::AddNewSymbol()
{
}

void UUWTuringMachine::AddNewState()
{
}

void UUWTuringMachine::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//NewStateButton->OnClick
}
