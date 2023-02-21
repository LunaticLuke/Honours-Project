// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateVariableMachine.h"

#include "CreateVariableUI.h"
#include "Components/ArrowComponent.h"


// Sets default values
ACreateVariableMachine::ACreateVariableMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Machine Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);

	CreateVariableUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Create Variable UI"));
	CreateVariableUI->SetupAttachment(StaticMeshComponent);

	ConveyorBeltMachine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConveyorBeltMesh"));
	ConveyorBeltMachine->SetupAttachment(StaticMeshComponent);

	SpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Location"));
	SpawnLocation->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void ACreateVariableMachine::BeginPlay()
{
	Super::BeginPlay();
	Cast<UCreateVariableUI>(CreateVariableUI->GetWidget())->SetupButtons(this);
	bNameAssigned = true;
}

// Called every frame
void ACreateVariableMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void ACreateVariableMachine::CreateVariable()
{
	if(DataTypeToCreate != NodeDataTypes::Unassigned) //Check that the player has actually assigned a variable as a variable needs a data type.
	{
		if(bNameAssigned) //Check that the player has actually assigned a name as variables need a name.
		{
			LastCreatedVariable =  GetWorld()->SpawnActor<AVariableNodeActor>(DefaultVariableNode,SpawnLocation->GetComponentLocation(),SpawnLocation->GetComponentRotation());
			LastCreatedVariable->AddForce(SpawnLocation->GetComponentLocation(),SpawnLocation->GetComponentLocation() * 100);
			LastCreatedVariable->SetDataType(DataTypeToCreate);
			LastCreatedVariable->SetVariableName(VariableName);
			LastCreatedVariable->SetVariableValue(VariableValue);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You need to name the variable before it can be created."));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You need to assign a data type to the variable before it can be created"));
	}

	DataTypeToCreate = NodeDataTypes::Unassigned;
	VariableName = "";
	VariableValue = "";
	VariableNumberValue = 0;
	bNameAssigned = false;
	bStartingValueAssigned = false;
	bNumberVariable = false;
}

void ACreateVariableMachine::SetDataType(NodeDataTypes TypeToAssign)
{
	DataTypeToCreate = TypeToAssign;
	if(TypeToAssign == NodeDataTypes::Char || TypeToAssign ==NodeDataTypes::String) //String and char can be represented as a string;
	{
		bNumberVariable = false;
	}else
	{
		bNumberVariable = true; //Bool, float and int can be represented as number;
	}
	bStartingValueAssigned = false;
	VariableValue = "";
	VariableNumberValue = 0;
}

void ACreateVariableMachine::AddToVariableName(FString NameToAssign)
{
	VariableName = VariableName + NameToAssign;
	if(VariableName.Len() > 0)
	{
		bNameAssigned = true;
	}
}

void ACreateVariableMachine::AddToVariableStartingValue(FString ValueToAssign, bool IsNumber)
{
	if(IsNumber)
	{
		bNumberVariable = true;
		VariableValue += VariableValue + ValueToAssign;
		VariableNumberValue = FCString::Atod(*VariableValue);
	}
	else
	{
		bNumberVariable = false;
		VariableValue = VariableValue + ValueToAssign;
	}
	bStartingValueAssigned = true;
}

