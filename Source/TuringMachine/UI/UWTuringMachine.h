// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TMManager.h"
#include "UWState.h"
#include "UWSymbol.h"
#include "UWTuringMachine.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TURINGMACHINE_API UUWTuringMachine : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void InitializeFromData();

	UFUNCTION()
	void AddNewSymbol();

	UFUNCTION()
	void AddNewState();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UUWButton* NewSymbolButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UUWButton* NewStateButton;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUWButton> ButtonWidgetClass;

	UPROPERTY()
	TArray<UUserWidget*> StateWidgets;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* SymbolPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* StatePanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATMManager* Manager;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUWSymbol> SymbolWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUWState> StateWidgetClass;

private:


	void NativeOnInitialized() override;

};
