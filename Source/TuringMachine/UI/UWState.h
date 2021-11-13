// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMManager.h"
#include "UWReaction.h"
#include "Blueprint/UserWidget.h"
#include "UWState.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TURINGMACHINE_API UUWState : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<UUWReaction*> Reactions;

	//UPROPERTY()
	FStateStruct* LinkedStateStruct;

	//UUWState(FStateStruct* State): LinkedStateStruct(State) {}

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* StateLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* MainPanel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUWReaction> ReactionWidgetClass;

	UFUNCTION(BlueprintCallable)
	void InitializeFromData();

protected:
	virtual void NativeOnInitialized() override;

private:


};
