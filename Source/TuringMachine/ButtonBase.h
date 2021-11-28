// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonBase.generated.h"

UCLASS()
class TURINGMACHINE_API AButtonBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void HandlePressed(AActor* Actor, FKey Key);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonPressed(AActor* Actor, FKey Key);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayPressedAnim();

	UPROPERTY(BlueprintReadWrite)
	bool bActive;
	
};
