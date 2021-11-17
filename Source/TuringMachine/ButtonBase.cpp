// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonBase.h"

// Sets default values
AButtonBase::AButtonBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddDynamic(this, &AButtonBase::OnButtonPressed);
}

// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

