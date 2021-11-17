// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "FileHelpers.h"

#include "TMManager.generated.h"

/**
 * 
 */

class ATape;

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

USTRUCT(BlueprintType)
struct FTapeActionStruct
{
	GENERATED_BODY()

	FString StateName;
	FString CurrentSymbol;
	FReactionStruct Reaction;
};

UCLASS(Blueprintable)
class TURINGMACHINE_API ATMManager : public AInfo
{
	GENERATED_BODY()

private:
	TArray<FString> Rows;

	UPROPERTY()
	int TapePointer;

	bool bForceFinish = false;

	int MaxTapeLength = 20;

	//UFUNCTION()
	void ExecuteReaction(FReactionStruct* Reaction);

	UFUNCTION()
	void InitializeTape();

	UFUNCTION()
	void MoveTapePointer(EMoveReaction Move);

	FString CurrentSymbol;

	UPROPERTY()
	TArray<FString> DefaultTape;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString FilePath; // = TEXT("C:\Users\Admin\Downloads\Test.csv");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ErrorSymbol;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ClearSymbol;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ReactionSeparator = TEXT(" ");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString CSVSeparator = TEXT(",");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString FinalStateSymbol = TEXT("qf");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATape* TapeActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxSolveIterations = 100;

	UPROPERTY(BlueprintReadOnly)
	TArray<FStateStruct> States;

	UFUNCTION(BlueprintCallable)
	void ParseDataFromFile();

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Alphabet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> Tape;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FTapeActionStruct> TapeActionStack;

	ATMManager();

	UFUNCTION(BlueprintCallable)
	void Simulate();

	UFUNCTION(BlueprintCallable)
	void ResetTuringMachine();

	UFUNCTION()
	void FinishTuringMachine();

	/*UFUNCTION(BlueprintCallable)
	void GenerateTape*/

	//UPROPERTY()
	FStateStruct* CurrentState;
};
