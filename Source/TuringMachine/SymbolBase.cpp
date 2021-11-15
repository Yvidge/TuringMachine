// Fill out your copyright notice in the Description page of Project Settings.


#include "SymbolBase.h"

// Sets default values
ASymbolBase::ASymbolBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASymbolBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASymbolBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//void ASymbolBase::SetSymbol(FString NewSymbol)
//{
//	
//}


void ASymbolBase::SetIndex(int NewIndex)
{
	Index = NewIndex;
}
