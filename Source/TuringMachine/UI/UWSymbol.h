// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWSymbol.generated.h"

/**
 * 
 */
UCLASS()
class TURINGMACHINE_API UUWSymbol : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SymbolLabel;

	UFUNCTION(BlueprintCallable)
	void SetText(FText Text);
	
};
