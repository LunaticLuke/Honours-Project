// Fill out your copyright notice in the Description page of Project Settings.


#include "Wand.h"

#include "Components/ArrowComponent.h"

// Sets default values
AWand::AWand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WandMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wand Static Mesh"));
	SetRootComponent(WandMeshComponent);

	WandOrigin = CreateDefaultSubobject<UArrowComponent>(TEXT("Wand origin"));
	WandOrigin->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
