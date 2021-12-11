// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMManager.h"
#include "Blueprint/UserWidget.h"
#include "UWEditableReaction.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TURINGMACHINE_API UUWEditableReaction : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsStateCorrect(const FText State, const ATMManager *Manager);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsSymbolCorrect(const FText Symbol, const ATMManager* Manager);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsMoveCorrect(const FText Move, const ATMManager* Manager);

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* StateLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* SymbolLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* MoveLabel;

	FReactionStruct* LinkedReactionStruct;

	UFUNCTION()
	void InitializeFromData();

	UFUNCTION(BlueprintCallable)
	void UpdateLinkedStruct();

	UFUNCTION(BlueprintCallable)
	void ChangeErrorStatus();
};
