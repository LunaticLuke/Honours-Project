// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgramManager.h"

#include "NodeConsoleManager.h"
#include "Nodes/FunctionNode.h"
#include "Nodes/VariableNodeActor.h"
#include "Nodes/NodeActor.h"



// Sets default values
AProgramManager::AProgramManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProgramManager::BeginPlay()
{
	Super::BeginPlay();
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

