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
};
