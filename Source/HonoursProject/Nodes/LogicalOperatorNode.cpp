// Fill out your copyright notice in the Description page of Project Settings.


#include "LogicalOperatorNode.h"

#include "VariableNodeActor.h"
#include "Components/TextRenderComponent.h"

ALogicalOperatorNode::ALogicalOperatorNode()
{
	ReturnType = NodeDataTypes::Bool;
	
}

ELogicalOperators ALogicalOperatorNode::GetLogicalOperator()
{
	return  LogicalOperator;
}

void ALogicalOperatorNode::BeginPlay()
{
	Super::BeginPlay();
	DisplayText();
	

	//Only need one parameter for a not node.
	if(LogicalOperator == ELogicalOperators::Not)
	{
		Parameter2Mesh->SetVisibility(false);
		Parameter2Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Parameter1Mesh->SetRelativeLocation(Parameter2Mesh->GetRelativeLocation());
		Parameters.Pop(true);
	}
	
}

void ALogicalOperatorNode::ExecuteNode()
{
	Super::ExecuteNode();

	TArray<FString> ParamValues;

	for(int i = 0; i < Parameters.Num();i++)
	{
		if(Parameters[i].FunctionNodeActor)
		{
			FString StringValue;
			double EmptyDouble;

			Parameters[i].FunctionNodeActor->ExecuteNode();
			
			Parameters[i].FunctionNodeActor->ReturnValue(StringValue,EmptyDouble);
			ParamValues.Push(StringValue);
		}
		else
		{
			ParamValues.Push(Manager->GetVariableNode(Parameters[i].VariableNodeActor->GetVariableName())->GetVariableValue());
		}
	}

	switch (LogicalOperator)
	{
	case ELogicalOperators::Or:
		if(ParamValues[0] == "true" || ParamValues[1] == "true")
		{
			WordReturn = "true";
		}
		else
		{
			WordReturn = "false";
		}
		break;
	case ELogicalOperators::And:
		if(ParamValues[0] == "true" && ParamValues[1] == "true")
		{
			WordReturn = "true";
		}
		else
		{
			WordReturn = "false";
		}
		break;
	case ELogicalOperators::Not:
		if(ParamValues[0] == "true")
		{
			WordReturn = "false";
		}
		else
		{
			WordReturn = "true";
		}
		break;
	default: ;
	}
}

bool ALogicalOperatorNode::IsThereCompileError()
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
	return false;
}

void ALogicalOperatorNode::DisplayText()
{
	TextComponentMessage = "";
	if(LogicalOperator == ELogicalOperators::Not)
	{
		TextComponentMessage = "!";
		if(Parameters[0].FunctionNodeActor)
		{
			TextComponentMessage = TextComponentMessage + Parameters[0].FunctionNodeActor->GetTextComponentMessage();
		}
		else if(Parameters[0].VariableNodeActor)
		{
			TextComponentMessage = TextComponentMessage + Parameters[0].VariableNodeActor->GetVariableName();
		}
		else
		{
			TextComponentMessage = TextComponentMessage + "(Bool Data Type)";
		}
	}
	else
	{
		if(Parameters[0].FunctionNodeActor)
		{
			TextComponentMessage = " (" + Parameters[0].FunctionNodeActor->GetTextComponentMessage() + ") ";
		}else if(Parameters[0].VariableNodeActor)
		{
			TextComponentMessage = Parameters[0].VariableNodeActor->GetVariableName();
		}
		else
		{
			TextComponentMessage = "(Bool Data Type)";
		}

		if(LogicalOperator == ELogicalOperators::And)
		{
			TextComponentMessage = TextComponentMessage + " && ";
		}else if(LogicalOperator == ELogicalOperators::Or)
		{
			TextComponentMessage = TextComponentMessage + "||";
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
			TextComponentMessage =TextComponentMessage + "(Bool Data Type)";
		}
	}
	NodeTextComponent->SetText(FText::FromString(TextComponentMessage));
}








