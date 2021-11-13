// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMManager.h"
#include "Blueprint/UserWidget.h"
#include "UWReaction.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TURINGMACHINE_API UUWReaction : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* StateLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SymbolLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MoveLabel;

	FReactionStruct* LinkedReactionStruct;

	UFUNCTION()
	void InitializeFromData();
};
