// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWState.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UUWState::InitializeFromData()
{
	if (LinkedStateStruct)
	{
		StateLabel->SetText(FText::FromString(LinkedStateStruct->Name));
		for (FReactionStruct Reaction : LinkedStateStruct->Reactions)
		{
			UUWReaction* CreatedReaction = CreateWidget<UUWReaction>(this, ReactionWidgetClass);
			Reactions.Add(CreatedReaction);
			CreatedReaction->LinkedReactionStruct = &Reaction;
			CreatedReaction->InitializeFromData();
			MainPanel->AddChild(CreatedReaction);
		}

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("INIT ERROR IN UWSTATE"));
	}
}

void UUWState::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}
