// Fill out your copyright notice in the Description page of Project Settings.


#include "VariableNodeActor.h"
#include "Components/TextRenderComponent.h"


// Sets default values
AVariableNodeActor::AVariableNodeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	
}

// Called when the game starts or when spawned
void AVariableNodeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVariableNodeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DisplayText();
}

void AVariableNodeActor::SetDataType(NodeDataTypes TypeToSet)
{
	VariableDataType = TypeToSet;
}

NodeDataTypes AVariableNodeActor::GetDataType()
{
	return VariableDataType;
}

void AVariableNodeActor::SetVariableValue(FString ValueToSet)
{
	VariableValue = ValueToSet;
}

FString AVariableNodeActor::GetVariableValue()
{
	return VariableValue;
}

void AVariableNodeActor::SetNumberValue(double NumberToSet)
{
	VariableNumberValue = NumberToSet;
}

double AVariableNodeActor::GetNumberValue()
{
	return VariableNumberValue;
}

void AVariableNodeActor::SetVariableName(FString NameToSet)
{
	VariableName = NameToSet;
}

FString AVariableNodeActor::GetVariableName()
{
	return VariableName;
}


void AVariableNodeActor::SetLineDeclared(int LineToSet)
{
	LineDeclaredAt = LineToSet;
}


int AVariableNodeActor::GetLineDeclaredAt()
{
	return LineDeclaredAt;
}

void AVariableNodeActor::SetVariableAssignedValueBool(bool BoolToSet)
{
	bAssignedTo = BoolToSet;
	
}

bool AVariableNodeActor::IsVariableAssignedValue()
{
	return bAssignedTo;
}

void AVariableNodeActor::DisplayText()
{
	FString StringToSet;
	if(VariableDataType == NodeDataTypes::String || VariableDataType == NodeDataTypes::Char || VariableDataType == NodeDataTypes::Bool)
	{
		StringToSet =EnumManager::ConvertDataTypeToString(VariableDataType) +" " + VariableName + " = " + VariableValue;
	}

	else{
		StringToSet =EnumManager::ConvertDataTypeToString(VariableDataType) +" " + VariableName + " = " + FString::SanitizeFloat(VariableNumberValue);
	}
		NodeTextComponent->SetText(FText::FromString(StringToSet));
}
