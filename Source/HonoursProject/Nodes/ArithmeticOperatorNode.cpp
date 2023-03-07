// Fill out your copyright notice in the Description page of Project Settings.


#include "ArithmeticOperatorNode.h"

#include "VariableNodeActor.h"
#include "Components/TextRenderComponent.h"
#include "HonoursProject/ProgramManager.h"

AArithmeticOperatorNode::AArithmeticOperatorNode()
{
	ReturnType = NodeDataTypes::Int;
}

void AArithmeticOperatorNode::BeginPlay()
{

	Super::BeginPlay();
	DisplayText();
}

void AArithmeticOperatorNode::ExecuteNode()
{
	ParameterValues.Empty();

	for(int i = 0; i < Parameters.Num();i++)
	{
		if(Parameters[i].FunctionNodeActor)
		{
			FString EmptyString;
			double NumberContainer;
			
			Parameters[i].FunctionNodeActor->ExecuteNode();
			
			Parameters[i].FunctionNodeActor->ReturnValue(EmptyString,NumberContainer);
			ParameterValues.Push(NumberContainer);
		}
		else
		{
			ParameterValues.Push(Manager->GetVariableNode(Parameters[i].VariableNodeActor->GetVariableName())->GetNumberValue());
		}
	}
		int ParameterValue1 = ParameterValues[0];
		int ParameterValue2 = ParameterValues[1]; //Create int versions for the modulus operator

	GEngine->AddOnScreenDebugMessage(INDEX_NONE,200,FColor::Green,FString::Printf(TEXT("Arithmetic: %f,%f"),ParameterValues[0],ParameterValues[1]));
	switch (ArithmeticOperation)
	{
	case ArithmeticOperatorType::Addition:
		NumberReturn = ParameterValues[0] + ParameterValues[1];
		break;
	case ArithmeticOperatorType::Subtraction:
	NumberReturn = ParameterValues[0] - ParameterValues[1];
		break;
	case ArithmeticOperatorType::Division:
	NumberReturn = ParameterValues[0] / ParameterValues[1];
		break;
	case ArithmeticOperatorType::Multiplication:
		NumberReturn = ParameterValues[0] * ParameterValues[1];
		break;
	case ArithmeticOperatorType::Modulus:
		NumberReturn = ParameterValue1 % ParameterValue2;
		break;
	default: ;
	}
	
}

bool AArithmeticOperatorNode::IsThereCompileError()
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

			//Parameters[i].FunctionNodeActor->ExecuteNode(); //Execute Nodes

			if((Parameters[i].FunctionNodeActor->GetNumberReturnValue() == 0 && ArithmeticOperation == ArithmeticOperatorType::Division) || (Parameters[i].FunctionNodeActor->GetNumberReturnValue() == 0 && ArithmeticOperation == ArithmeticOperatorType::Modulus)) //Preventing Divide By Zero errors for modulus and division
			{
				ErrorMessage = "This program would cause a Divide By Zero error and would crash. Please ensure that values are not zero when dividing or using the modulus operator";
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

void AArithmeticOperatorNode::DisplayText()
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
		TextComponentMessage = "Type: Float Or Int";
	}

	switch (ArithmeticOperation)
	{
	case ArithmeticOperatorType::Addition:
		TextComponentMessage = TextComponentMessage + " + ";
		break;
	case ArithmeticOperatorType::Subtraction:
		TextComponentMessage = TextComponentMessage + " - ";
		break;
	case ArithmeticOperatorType::Division:
		TextComponentMessage = TextComponentMessage + " / ";
		break;
	case ArithmeticOperatorType::Multiplication:
		TextComponentMessage = TextComponentMessage + " * ";
		break;
	case ArithmeticOperatorType::Modulus:
		TextComponentMessage = TextComponentMessage + " % ";
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
		TextComponentMessage = TextComponentMessage + " Type: Float Or Int";
	}
	
	NodeTextComponent->SetText(FText::FromString(TextComponentMessage));
	
}

ArithmeticOperatorType AArithmeticOperatorNode::GetArithmeticOperatorType()
{
	return ArithmeticOperation;
}
