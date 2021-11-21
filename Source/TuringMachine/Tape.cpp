// Fill out your copyright notice in the Description page of Project Settings.


#include "Tape.h"
#include "TMManager.h"
// Sets default values
ATape::ATape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(Root);
	SymbolsAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("SymbolsAnchor"));
	SymbolsAnchor->SetupAttachment(Root);
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
	CreatedSymbols.Empty();

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
			CreatedSymbol->AttachToComponent(SymbolsAnchor, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		}

		FVector Loc(CreatedSymbols[CreatedSymbols.Num()/2]->GetActorLocation());
		FVector RelativeLoc = Head->GetRelativeLocation();
		RelativeLoc[0] = 0;
		Loc += RelativeLoc;
		Head->SetWorldLocation(Loc);

	}
}

void ATape::UpdateSymbolByIndex(int Index)
{
	CreatedSymbols[Index]->SetSymbol(Manager->Tape[Index]);
}

void ATape::UpdateSymbolByIndexWithAnim(int Index)
{
	if (CreatedSymbols[Index]->GetSymbol() != Manager->Tape[Index])
	{
		CreatedSymbols[Index]->SetSymbol(Manager->Tape[Index]);
		PlayHeadAnim();
	}
}

void ATape::MoveTape_Implementation(EMoveReaction Move)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("BRUH"));
	if (Move == R)
	{
		FVector Loc(-HorizontalSize, 0, 0);
		AddActorWorldOffset(Loc);
		Head->AddWorldOffset(-Loc);
	}
	if (Move == L)
	{
		FVector Loc(HorizontalSize, 0, 0);
		AddActorWorldOffset(Loc);
		Head->AddWorldOffset(-Loc);
	}
}

void ATape::NextAction()
{
}

void ATape::PreviousAction()
{
}

void ATape::SetSymbolByIndex(int Index, FString Symbol)
{
	CreatedSymbols[Index]->SetSymbol(Symbol);
}

FString ATape::GetSymbolByIndex(int Index)
{
	return CreatedSymbols[Index]->GetSymbol();
}



