// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "FileHelpers.h"
#include "TMManager.generated.h"

/**
 * 
 */

UENUM()
enum EMoveReaction
{
	L,
	R,
	N
};

USTRUCT(BlueprintType)
struct FReactionStruct
{
	GENERATED_BODY()

	FString NewState;

	FString NewChar;

	EMoveReaction Move;

	bool bError = 0;

};


USTRUCT(BlueprintType)
struct FStateStruct
{
	GENERATED_BODY()

	//FStateStruct()

	FString Name;
	TArray<FReactionStruct> Reactions;
	
};

UCLASS(Blueprintable)
class TURINGMACHINE_API ATMManager : public AInfo
{
	GENERATED_BODY()

private:
	TArray<FString> Rows;
	TArray<FString> Alphabet;
	

protected:
	virtual void BeginPlay() override;;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString FilePath; // = TEXT("C:\Users\Admin\Downloads\Test.csv");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ErrorSymbol;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ReactionSeparator = TEXT(" ");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString CSVSeparator = TEXT(",");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString FinalStateSymbol = TEXT("qf");

	UPROPERTY(BlueprintReadOnly)
	TArray<FStateStruct> States;

	UFUNCTION(BlueprintCallable)
	void ParseDataFromFile();

	ATMManager();

};
