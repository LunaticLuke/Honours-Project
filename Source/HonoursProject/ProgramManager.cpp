// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgramManager.h"

#include "BlueprintFunctionNodeSpawner.h"
#include "NodeAssemblyUI.h"
#include "NodeConsoleManager.h"
#include "Components/BoxComponent.h"
#include "Nodes/FunctionNode.h"
#include "Nodes/VariableNodeActor.h"
#include "Nodes/NodeActor.h"
#include "Nodes/WhileLoopNode.h"


// Sets default values
AProgramManager::AProgramManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NodePlacementZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Node Placement Zone"));

	Param1Zone = CreateDefaultSubobject<UBoxComponent>(TEXT("Param 1 Zone"));

	Param2Zone = CreateDefaultSubobject<UBoxComponent>(TEXT("Param 2 Zone"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
}

// Called when the game starts or when spawned
void AProgramManager::BeginPlay()
{
	Super::BeginPlay();

	Param1Zone->OnComponentBeginOverlap.AddDynamic(this,&AProgramManager::OnParameterOverlap);
	Param2Zone->OnComponentBeginOverlap.AddDynamic(this,&AProgramManager::OnParameterOverlap);
	NodePlacementZone->OnComponentBeginOverlap.AddDynamic(this,&AProgramManager::OnParameterOverlap);

	Param1Zone->OnComponentEndOverlap.AddDynamic(this,&AProgramManager::OnParameterEndOverlap);
	Param2Zone->OnComponentEndOverlap.AddDynamic(this,&AProgramManager::OnParameterEndOverlap);
	NodePlacementZone->OnComponentEndOverlap.AddDynamic(this,&AProgramManager::OnParameterEndOverlap);

	AssemblyUI = Cast<UNodeAssemblyUI>(WidgetComponent->GetWidget());
	
	Console->InitUI(this);

	for(int i = 0; i < FunctionNodes.Num();i++)
	{
		NodeLocations.Push(FunctionNodes[i]->GetActorLocation());
	}
	GetWorld()->GetTimerManager().SetTimer(Ticker,this,&AProgramManager::NodeCheck,0.2f,true,0.2f);
}

void AProgramManager::DisplayVariables()
{
	for(int i = 0; i < ProgramVariables.Num();i++)
	{
		if(ProgramVariables[i]->GetDataType() == NodeDataTypes::String || ProgramVariables[i]->GetDataType() == NodeDataTypes::Char || ProgramVariables[i]->GetDataType() == NodeDataTypes::Bool)
		{
			Console->AddToLog(EnumManager::ConvertDataTypeToString(ProgramVariables[i]->GetDataType()) + " " + ProgramVariables[i]->GetVariableName() + " = " + VariableData[i].CurrentTextValue);
		}
		else
		{
			Console->AddToLog(EnumManager::ConvertDataTypeToString(ProgramVariables[i]->GetDataType()) + " " + ProgramVariables[i]->GetVariableName() + " = " + FString::SanitizeFloat(VariableData[i].CurrentNumberValue));
		}
	}
}

void AProgramManager::OnParameterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	
	if(OverlappedComponent == Param1Zone)
	{
		ANodeActor* Act1 = Cast<ANodeActor>(OtherActor);
		if(Act1 && Param1Actor == nullptr)
		{
			Param1Actor = Act1;
		}
	}
		
	else if(OverlappedComponent == Param2Zone)
	{
		ANodeActor* Act2 = Cast<ANodeActor>(OtherActor);
		if(Act2 && Param2Actor == nullptr)
		{
			Param2Actor = Act2;
		}
	}
	
	else if(OverlappedComponent == NodePlacementZone)
	{
		AFunctionNode* FuncAct = Cast<AFunctionNode>(OtherActor);
		if(FuncAct && NodeActor == nullptr)
		{
			NodeActor = FuncAct;
			NodeActor->bCombinable = true;
			AssemblyUI->SetImage(OtherActor->GetClass());
		}
	}
	
}

void AProgramManager::OnParameterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	 if(OverlappedComponent == Param1Zone)
	 {
		 ANodeActor* Act1 = Cast<ANodeActor>(OtherActor);
	 	if(Act1)
	 	{
	 		if(Act1 == Param1Actor)
	 		{
	 			Param1Actor = nullptr;
	 		}
	 	}
	 }

	else if(OverlappedComponent == Param2Zone)
	{
		ANodeActor* Act2 = Cast<ANodeActor>(OtherActor);
		if(Act2)
		{
			if(Act2 == Param2Actor)
			{
				Param2Actor = nullptr;
			}
		}
	}


	else if(OverlappedComponent == NodePlacementZone)
	{
		AFunctionNode* FuncAct = Cast<AFunctionNode>(OtherActor);
		if(FuncAct)
		{
			if(FuncAct == NodeActor)
			{
				NodeActor->bCombinable = false;
				NodeActor = nullptr;
				AssemblyUI->ResetImage();
			}
		}
	}

}


void AProgramManager::NodeCheck()
{
	for(int i = 0; i < FunctionNodes.Num();i++)
	{
		if(FVector::Distance(FunctionNodes[i]->GetActorLocation(),NodeLocations[i]) >= 300.0f)
		{
			GEngine->AddOnScreenDebugMessage(0,10.0f,FColor::Cyan,TEXT("It's working"));
			FActorSpawnParameters SpawnInfo;
			FunctionNodes[i] = GetWorld()->SpawnActor<AFunctionNode>(FunctionNodes[i]->GetClass(),NodeLocations[i],FRotator(0,0,0),SpawnInfo);
			FunctionNodes[i]->SetActorScale3D(FVector(0.5,0.2,0.2));
			FunctionNodes[i]->SetActorLocation(NodeLocations[i]);
			FunctionNodes[i]->Manager = this;
		}
	}
	
}

// Called every frame
void AProgramManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProgramManager::AddFunctionToProgram(AFunctionNode* FunctionToAdd)
{
	
		ProgramExecution.Push(FunctionToAdd);
		FunctionToAdd->bAddedToProgram = true;
	
	Console->DisplayProgramExecution(FunctionToAdd);
}

void AProgramManager::RunProgram()
{
//Reset Variable Values Whenever The User Chooses To Run Program
	for(int i = 0; i < ProgramVariables.Num();i++)
	{
		VariableData[i].CurrentNumberValue = VariableData[i].StartingNumberValue;
		VariableData[i].CurrentTextValue = VariableData[i].StartingTextValue;
		ProgramVariables[i]->SetVariableValue(VariableData[i].CurrentTextValue);
		ProgramVariables[i]->SetNumberValue(VariableData[i].CurrentNumberValue);
	}
	
	bool FoundError =  false;
	for(int i = 0; i < ProgramExecution.Num();i++)
	{
		//Check that the node isnt part of a function, if it is, the execution will be handled when we call execute on the parent node. Hence, doesnt need to be executed here.
		if(!ProgramExecution[i]->bWithinFunction)
		{
			if(ProgramExecution[i]->ReturnType != NodeDataTypes::Unassigned) //If the function isn't void, it should be assigned to or used within a statement. Functions with a return type cannot just be called like other nodes.
				{
				FString ErrorMessage = "Function Of Return Type " + EnumManager::ConvertDataTypeToString(ProgramExecution[i]->ReturnType) + " Is Unassigned To";
				Console->AddToLog(ErrorMessage);
				//break;
				}
		
			FoundError = ProgramExecution[i]->IsThereCompileError();
			if(FoundError)
			{
				Console->AddToLog(ProgramExecution[i]->GetErrorMessage());
				break;
			}
			else
			{
				ProgramExecution[i]->ExecuteNode();
				if(ProgramExecution[i]->IsA(AWhileLoopNode::StaticClass()))
				{
					if(Cast<AWhileLoopNode>(ProgramExecution[i])->bPotentialInfiniteLoop)
					{
						FString ErrorMessage = "While Loop Is Either Infinite Or Longer Than Expected For Solution";
						Console->AddToLog(ErrorMessage);
						break;
					}
				}
			}
		}
	}
	DisplayVariables();
}

void AProgramManager::AddVariableToProgram(AVariableNodeActor* VariableToAdd)
{
 bool bFound = false;
	for(int i =0; i < ProgramVariables.Num(); i++)
	{
		if(ProgramVariables[i]->GetVariableName() ==  VariableToAdd->GetVariableName())
		{
			bFound = true; //Already Added
		}
	}

	if(!bFound)
	{
		ProgramVariables.Push(VariableToAdd);
		FVariableProgramData Data;
		Data.StartingTextValue = VariableToAdd->GetVariableValue();
		Data.StartingNumberValue = VariableToAdd->GetNumberValue();
		Data.CurrentTextValue = Data.StartingTextValue;
		Data.CurrentNumberValue = Data.StartingNumberValue;
		VariableData.Push(Data);
		Console->DisplayVariable(VariableToAdd);
	}
}

AVariableNodeActor* AProgramManager::GetVariableNode(FString VariableName)
{
	for(int i = 0; i < ProgramVariables.Num();i++)
	{
		if(ProgramVariables[i]->GetVariableName() == VariableName)
		{
			return ProgramVariables[i];
		}
	}

	return nullptr;
}

void AProgramManager::SetVariableValue(FString VariableName, FString TextValue, double NumberValue)
{
	for(int i = 0; i < ProgramVariables.Num();i++)
	{
		if(ProgramVariables[i]->GetVariableName() == VariableName)
		{
			VariableData[i].CurrentTextValue = TextValue;
			VariableData[i].CurrentNumberValue = NumberValue;
			ProgramVariables[i]->SetVariableValue(TextValue);
			ProgramVariables[i]->SetNumberValue(NumberValue);
		}
	}
}

ANodeConsoleManager* AProgramManager::GetConsole()
{
	return Console;
}

ANodeActor* AProgramManager::GetParamActor(int ParamNumber)
{
	switch (ParamNumber)
	{
	case 1:
	return Param1Actor;
		break;

	case 2:
		return  Param2Actor;
		break;
	default: return nullptr;break;;
	}
}

AFunctionNode* AProgramManager::GetNodeActor()
{
	return NodeActor;
}

void AProgramManager::Undo()
{
	if(ProgramExecution.Num() > 0)
	{
		AActor* UndoneNode = ProgramExecution[ProgramExecution.Num() - 1];
		ProgramExecution[ProgramExecution.Num() - 1]->bAddedToProgram = false;
		ProgramExecution.Pop();
		Console->ClearLog();
		for(int i = 0; i < ProgramVariables.Num();i++)
		{
			Console->DisplayVariable(ProgramVariables[i]);
		}
		for(int i = 0; i < ProgramExecution.Num();i++)
		{
			Console->DisplayProgramExecution(ProgramExecution[i]);
		}
		UndoneNode->SetActorLocation(UndoPoint->GetActorLocation());
		UndoneNode->SetActorHiddenInGame(false);
	}
}

void AProgramManager::ClearProgram()
{
	//ProgramVariables.Empty();
	//ProgramExecution.Empty();

	for(int i = 0; i < ProgramVariables.Num(); i++)
	{
		ProgramVariables.Pop();
	}
	for(int i = 0; i < ProgramExecution.Num();i++)
	{
		ProgramExecution.Pop();
	}
	for(int i = 0; i < VariableData.Num();i++)
	{
		VariableData.Pop();
	}
	Console->ClearLog();
}

