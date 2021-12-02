// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMManager.h"
#include "Blueprint/UserWidget.h"
#include "UWActionStackRow.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TURINGMACHINE_API UUWActionStackRow : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	class UTextBlock* StateLabel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	class UTextBlock* CurrentSymbolLabel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	class UUWReaction* ReactionLabel;

	UFUNCTION()
	void InitializeFromData(const FTapeActionStruct& Action);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHighlighting(bool Value);
};
