// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentNode.h"

#include "VariableNodeActor.h"
#include "Components/TextRenderComponent.h"

void AAssignmentNode::BeginPlay()
{
	Super::BeginPlay();
	Parameters[0].VariableSlot = true;
	DisplayText();
}

void AAssignmentNode::ExecuteNode()
{
	Super::ExecuteNode();

	FString TextValue;
	double NumberValue;

	//Check whether parameter 2 is a variable being passed in or function. 
	if(Parameters[1].VariableNodeActor)
	{
		TextValue = Manager->GetVariableNode(Parameters[1].VariableNodeActor->GetVariableName())->GetVariableValue();
		NumberValue = Manager->GetVariableNode(Parameters[1].VariableNodeActor->GetVariableName())->GetNumberValue();
	}
	else
	{
		Parameters[1].FunctionNodeActor->ExecuteNode();
		TextValue = Parameters[1].FunctionNodeActor->GetWordReturnValue();
		NumberValue = Parameters[1].FunctionNodeActor->GetNumberReturnValue();
	}
	
	
	Manager->SetVariableValue(Parameters[0].VariableNodeActor->GetVariableName(),TextValue,NumberValue);
	
}

bool AAssignmentNode::IsThereCompileError()
{
	for(int i = 0; i < Parameters.Num();i++)
	{
		if(Parameters[i].FunctionNodeActor)
		{
			if(Parameters[i].FunctionNodeActor->IsThereCompileError()) //If function assigned has a compile error, break out.
				{
				ErrorMessage = Parameters[i].FunctionNodeActor->GetErrorMessage();
				return true;
				}

			//Parameters[i].FunctionNodeActor->ExecuteNode(); //Execute Node
		}
		else if(Parameters[i].VariableNodeActor)
		{
			AVariableNodeActor* VariableCheck = Manager->GetVariableNode(Parameters[i].VariableNodeActor->GetVariableName());

			if(!VariableCheck) //Undeclared Variable
				{
				ErrorMessage = "No such variable called " + Parameters[i].VariableNodeActor->GetVariableName() + " declared within the program.";
				return true;
				}
		}
		else
		{
			ErrorMessage = "Parameters Missing";
			return true;
		}
	}
	//Check if trying to assign incorrect data types to each other.
	if(Parameters[0].CurrentParameterDataType != Parameters[1].CurrentParameterDataType) 
	{
		ErrorMessage = "Cannot Assign Value Of Type " + EnumManager::ConvertDataTypeToString(Parameters[1].CurrentParameterDataType) + " to a variable of type " + EnumManager::ConvertDataTypeToString(Parameters[0].CurrentParameterDataType);
		return  true;
	}
	
	return false;
}

void AAssignmentNode::DisplayText()
{
	TextComponentMessage = ""; //Start fresh with empty string.
	if(Parameters[0].VariableNodeActor)
	{
		TextComponentMessage = Parameters[0].VariableNodeActor->GetVariableName() + " = ";
	}
	else
	{
		TextComponentMessage = "Type: Variable Node = ";
	}

	if(Parameters[1].VariableNodeActor)
	{
		TextComponentMessage = TextComponentMessage + Parameters[1].VariableNodeActor->GetVariableName();
	}else if(Parameters[1].FunctionNodeActor)
	{
		TextComponentMessage = TextComponentMessage + Parameters[1].FunctionNodeActor->GetTextComponentMessage();
	}
	else
	{
		TextComponentMessage = TextComponentMessage + "Same Type As Variable 1";
	}
	NodeTextComponent->SetText(FText::FromString(TextComponentMessage));
}
