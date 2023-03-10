// Fill out your copyright notice in the Description page of Project Settings.


#include "AnswerBlock.h"

#include "Components/TextRenderComponent.h"

// Sets default values
AAnswerBlock::AAnswerBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block Mesh"));
	SetRootComponent(BlockMesh);

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Node Text"));
	TextComponent->SetupAttachment(BlockMesh);
}

// Called when the game starts or when spawned
void AAnswerBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnswerBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AAnswerBlock::GetAnswer()
{
	return Answer;
}

void AAnswerBlock::SetAnswer(FString AnswerToSet)
{
	Answer = AnswerToSet;
	TextComponent->SetText(FText::FromString(AnswerToSet));
}

