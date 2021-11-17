// Fill out your copyright notice in the Description page of Project Settings.


#include "Tape.h"
#include "TMManager.h"
// Sets default values
ATape::ATape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATape::BeginPlay()
{
	Super::BeginPlay();
	//GenerateTape();
}

// Called every frame
void ATape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATape::GenerateTape()
{
	for (ASymbolBase* Symbol : CreatedSymbols)
	{
		Symbol->Destroy();
	}

	if(Manager)
	{
		//Manager->
		float Offset = 0;
		for (int i = 0; i < Manager->Tape.Num(); ++i)
		{
			ASymbolBase* CreatedSymbol = GetWorld()->SpawnActor<ASymbolBase>(SymbolClass);
			CreatedSymbol->SetSymbol(Manager->Tape[i]);
			Offset += HorizontalSize;
			FVector Loc = GetActorLocation();
			Loc[0] += Offset;
			CreatedSymbol->SetActorLocation(Loc);
			CreatedSymbol->SetIndex(i);
			CreatedSymbols.Add(CreatedSymbol);

			
			//EAttachmentRule Rule(EAttachmentRule::SnapToTarget);
			CreatedSymbol->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		}
	}
}

void ATape::UpdateSymbolByIndex(int Index)
{
	CreatedSymbols[Index]->SetSymbol(Manager->Tape[Index]);
}



