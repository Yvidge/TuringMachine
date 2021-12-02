// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWTuringMachine.h"

#include "UWButton.h"
#include "UWState.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/EditableText.h"

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
		
		UUWSymbol* CreatedSpacer = CreateWidget<UUWSymbol>(this, SymbolWidgetClass);
		//WidgetTree->ConstructWidget<UTextBlock>();
		
			
		//SymbolPanel->AddChildToVerticalBox(CreatedSpacer);
		//CreatedSpacer->SetText(FText::FromString("a"));
		//FLinearColor Color(0, 0, 0, 0);
		//FSlateColor SlateColor(Color);
		//CreatedSpacer->SymbolLabel->WidgetStyle.ColorAndOpacity = SlateColor;
		////CreatedSpacer->SetOpacity(0.0f);
		//FSlateFontInfo Font;
		//Font.Size = 200;
		//Font.OutlineSettings.OutlineSize = 0;
		//CreatedSpacer->SymbolLabel->WidgetStyle.SetFont(Font);
		//CreatedSpacer->SetFont(Font);

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
