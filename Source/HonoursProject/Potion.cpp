// Fill out your copyright notice in the Description page of Project Settings.


#include "Potion.h"

// Sets default values
APotion::APotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PotionBottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Potion Bottle Mesh"));
	SetRootComponent(PotionBottleMesh);
}

// Called when the game starts or when spawned
void APotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APotion::SetProgram(TArray<FVariableProgramData> VariableArray, TArray<AFunctionNode*> ProgramArrayParam, TArray<AVariableNodeActor*> VariableNodeActors)
{
	PotionBottleMesh->SetMaterial(0,PotionMaterial);
	VariableData = VariableArray;
	ProgramVariables = VariableNodeActors;
	ProgramArray = ProgramArrayParam;
}

                                                                     