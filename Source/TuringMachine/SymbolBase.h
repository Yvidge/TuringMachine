// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SymbolBase.generated.h"

UCLASS(Abstract, Blueprintable)
class TURINGMACHINE_API ASymbolBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASymbolBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int Index;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetSymbol(const FString &NewSymbol);

	UFUNCTION(BlueprintImplementableEvent)
	const FString GetSymbol();

	UFUNCTION()
	void SetIndex(int NewIndex);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetIndex();
};
