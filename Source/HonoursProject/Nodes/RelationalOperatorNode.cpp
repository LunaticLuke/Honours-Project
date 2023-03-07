// Fill out your copyright notice in the Description page of Project Settings.


#include "RelationalOperatorNode.h"

#include "VariableNodeActor.h"
#include "Components/TextRenderComponent.h"

ARelationalOperatorNode::ARelationalOperatorNode()
{
}

ERelationalOperators ARelationalOperatorNode::GetRelationalOperator()
{
	return RelationalOperator;
}

void ARelationalOperatorNode::BeginPlay()
{
	Super::BeginPlay();
	DisplayText();
	

	if(RelationalOperator != ERelationalOperators::EqualTo && RelationalOperator != ERelationalOperators::NotEqualTo)
	{
		//Bools, strings and chars cannot be used for <,<=,>, and >=: remove them
		for(int i = 0; i < Parameters.Num(); i++)
		{
			Parameters[i].ValidDataTypes.Remove(NodeDataTypes::String);
			Parameters[i].ValidDataTypes.Remove(NodeDataTypes::Bool);
			Parameters[i].ValidDataTypes.Remove(NodeDataTypes::Char);
		}
	}
}

void ARelationalOperatorNode::ExecuteNode()
{
	Super::ExecuteNode();
	
	TArray<FString> StringValues;
	TArray<double> DoubleValues;

	for(int i = 0; i < Parameters.Num(); i++)
	{
		if(Parameters[i].FunctionNodeActor)
		{
			FString String;
			double Num;

			Parameters[i].FunctionNodeActor->ExecuteNode();
			Parameters[i].FunctionNodeActor->ReturnValue(String,Num);
			if(Parameters[i].FunctionNodeActor->ReturnType == NodeDataTypes::Float || Parameters[i].FunctionNodeActor->ReturnType == NodeDataTypes::Int)
			{
				DoubleValues.Push(Num);
			}
			else
			{
				StringValues.Push(String);
			}
		}
		else
		{
			if(Parameters[i].VariableNodeActor->GetDataType() == NodeDataTypes::Float || Parameters[i].VariableNodeActor->GetDataType() == NodeDataTypes::Int)
			{
				DoubleValues.Push(Parameters[i].VariableNodeActor->GetNumberValue());
			}
			else
			{
				StringValues.Push(Parameters[i].VariableNodeActor->GetVariableValue());
			}
		}
	}


	switch (RelationalOperator) {
	case ERelationalOperators::LessThan:
		WordReturn = (DoubleValues[0] < DoubleValues[1]) ? "true" : "false";
		break;
	case ERelationalOperators::LessThanEqualTo:
		WordReturn = (DoubleValues[0] <= DoubleValues[1]) ? "true" : "false";
		break;
	case ERelationalOperators::GreaterThan:
		WordReturn = (DoubleValues[0] > DoubleValues[1]) ? "true" : "false";
		break;
	case ERelationalOperators::GreaterThanEqualTo:
		WordReturn = (DoubleValues[0] >= DoubleValues[1]) ? "true" : "false";
		break;
	case ERelationalOperators::EqualTo:
		if(StringValues.Num() > 0)
		{
			WordReturn = (StringValues[0] == StringValues[1]) ? "true" : "false";
		}
		else
		{
			WordReturn = (DoubleValues[0] == DoubleValues[1]) ? "true" : "false";
		}
		break;
	case ERelationalOperators::NotEqualTo:
		if(StringValues.Num() > 0)
		{
			WordReturn = (StringValues[0] != StringValues[1]) ? "true" : "false";
		}
		else
		{
			WordReturn = (DoubleValues[0] != DoubleValues[1]) ? "true" : "false";
		}
		break;
	default: ;
	}
}

bool ARelationalOperatorNode::IsThereCompileError()
{
	for(int i = 0; i < Parameters.Num();i++)
	{
		if(Parameters[i].FunctionNodeActor)
		{
			if(Parameters[i].FunctionNodeActor->IsThereCompileError())
			{
				ErrorMessage = Parameters[i].FunctionNodeActor->GetErrorMessage();
				return true;
			}
			
		}
		else if(Parameters[i].VariableNodeActor)
		{
			AVariableNodeActor* VariableCheck = Manager->GetVariableNode(Parameters[i].VariableNodeActor->GetVariableName());

			if(!VariableCheck) //Undeclared Variable
				{
				ErrorMessage = "No such variable called " + Parameters[i].VariableNodeActor->GetVariableName() + " found within the program.";
				return true;
				}
		}
		else
		{
			ErrorMessage = "Parameters Missing";
			return true;
		}
	}
	if(Parameters[0].CurrentParameterDataType != Parameters[1].CurrentParameterDataType) 
	{
		ErrorMessage = "Cannot Assign Value Of Type " + EnumManager::ConvertDataTypeToString(Parameters[1].CurrentParameterDataType) + " to a variable of type " + EnumManager::ConvertDataTypeToString(Parameters[0].CurrentParameterDataType);
		return  true;
	}
	return false;
}

void ARelationalOperatorNode::DisplayText()
{
	TextComponentMessage = "";
	
	
		if(Parameters[0].FunctionNodeActor)
		{
			TextComponentMessage = " (" + Parameters[0].FunctionNodeActor->GetTextComponentMessage() + ") ";
		}else if(Parameters[0].VariableNodeActor)
		{
			TextComponentMessage = Parameters[0].VariableNodeActor->GetVariableName();
		}
		else
		{
			TextComponentMessage = "";
		}


	switch (RelationalOperator)
	{
	case ERelationalOperators::LessThan:
		TextComponentMessage = TextComponentMessage + " < ";
		break;
	case ERelationalOperators::LessThanEqualTo:
		TextComponentMessage = TextComponentMessage + " <= ";
		break;
	case ERelationalOperators::GreaterThan:
		TextComponentMessage = TextComponentMessage + " > ";
		break;
	case ERelationalOperators::GreaterThanEqualTo:
		TextComponentMessage = TextComponentMessage + " >= ";
		break;
	case ERelationalOperators::EqualTo:
		TextComponentMessage = TextComponentMessage + " == ";
		break;
	case ERelationalOperators::NotEqualTo:
		TextComponentMessage = TextComponentMessage + " != ";
		break;
	default: ;
	}

		if(Parameters[1].FunctionNodeActor)
		{
			TextComponentMessage = TextComponentMessage + " (" + Parameters[1].FunctionNodeActor->GetTextComponentMessage() + " )";
		}else if(Parameters[1].VariableNodeActor)
		{
			TextComponentMessage = TextComponentMessage +Parameters[1].VariableNodeActor->GetVariableName();
		}
		else
		{
			TextComponentMessage =TextComponentMessage + "";
		}
	
	NodeTextComponent->SetText(FText::FromString(TextComponentMessage));
}


