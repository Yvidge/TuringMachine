// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMManager.h"
#include "Blueprint/UserWidget.h"
#include "UWActionStack.generated.h"

/**
 * 
 */

class UUWActionStackRow;

UCLASS()
class TURINGMACHINE_API UUWActionStack : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void InitializeFromData(const TArray<FTapeActionStruct>& Actions);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	class UScrollBox* MainPanel;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUWActionStackRow> ActionRowClass;
};
