// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeActor.h"

#include "Components/TextRenderComponent.h"

// Sets default values
ANodeActor::ANodeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
	NodeStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Node Mesh"));
	SetRootComponent(NodeStaticMesh);

	NodeTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Node Text"));
	NodeTextComponent->SetTextRenderColor(FColor::Yellow);
	NodeTextComponent->SetupAttachment(NodeStaticMesh);
}

// Called when the game starts or when spawned
void ANodeActor::BeginPlay()
{
	Super::BeginPlay();

	DisplayText();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));	
}


// Called every frame
void ANodeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ANodeActor::DisplayText()
{
	NodeTextComponent->SetText(FText::FromString(TextComponentMessage));
}

void ANodeActor::ConfigurePhysics(bool PhysicsEnabled)
{
	NodeStaticMesh->SetSimulatePhysics(PhysicsEnabled);
}

void ANodeActor::AddForce(FVector Location, FVector Force)
{
	NodeStaticMesh->AddForceAtLocation(Force,Location);
}


FString ANodeActor::GetErrorMessage()
{
	return ErrorMessage;
}

FString ANodeActor::GetTextComponentMessage()
{
	return TextComponentMessage;
}



