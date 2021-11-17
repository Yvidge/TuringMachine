// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SymbolBase.h"

#include "GameFramework/Actor.h"
#include "Tape.generated.h"

class ATMManager;

UCLASS()
class TURINGMACHINE_API ATape : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATape();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<ASymbolBase*> CreatedSymbols;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void GenerateTape();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATMManager* Manager;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASymbolBase> SymbolClass;

	UPROPERTY(EditAnywhere)
	float HorizontalSize = 100;

	UFUNCTION()
	void UpdateSymbolByIndex(int Index);

};
