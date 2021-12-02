// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMManager.h"
#include "Blueprint/UserWidget.h"
#include "UWSymbol.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TURINGMACHINE_API UUWSymbol : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* SymbolLabel;

	UFUNCTION(BlueprintCallable)
	void SetText(FText Text);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText GetText();

	UFUNCTION(BlueprintCallable)
	void UpdateSymbolInAlphabet(const FString NewSymbol, ATMManager* Manager);

	UFUNCTION(BlueprintCallable)
	bool CheckIsNewSymbolUnique(const FString NewSymbol, const ATMManager* Manager);

	UPROPERTY(BlueprintReadWrite)
	FString PreviousSymbol;

};
