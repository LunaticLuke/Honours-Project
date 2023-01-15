// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalVariableNode.h"

// Sets default values
ALocalVariableNode::ALocalVariableNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	VariableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Node Mesh"));
}

// Called when the game starts or when spawned
void ALocalVariableNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALocalVariableNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALocalVariableNode::SetDataType(NodeDataTypes TypeToSet)
{
	VariableDataType = TypeToSet;
}

NodeDataTypes ALocalVariableNode::GetDataType()
{
	return VariableDataType;
}

void ALocalVariableNode::SetVariableValue(FString ValueToSet)
{
	VariableValue = ValueToSet;
}

FString ALocalVariableNode::GetVariableValue()
{
	return VariableValue;
}

