// Fill out your copyright notice in the Description page of Project Settings.


#include "PrintNode.h"

#include "VariableNodeActor.h"
#include "Components/TextRenderComponent.h"
#include "HonoursProject/NodeConsoleManager.h"

void APrintNode::BeginPlay()
{
	Super::BeginPlay();
	Parameter2Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Parameter2Mesh->SetHiddenInGame(true);
}

void APrintNode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APrintNode::ExecuteNode()
{
	Super::ExecuteNode();

	FString ValueToPrint = "";
	
	if(Parameters[0].FunctionNodeActor)
	{
		ValueToPrint = Parameters[0].FunctionNodeActor->GetWordReturnValue();
	}else if(Parameters[0].VariableNodeActor)
	{
		ValueToPrint = Parameters[0].VariableNodeActor->GetVariableValue();
	}
	
	Manager->GetConsole()->AddToLog(ValueToPrint);
}

bool APrintNode::IsThereCompileError()
{
	if(Parameters[0].FunctionNodeActor)
	{
		if(Parameters[0].FunctionNodeActor->IsThereCompileError())
		{
			ErrorMessage = Parameters[0].FunctionNodeActor->GetErrorMessage();
			return true;
		}
		//Parameters[i].FunctionNodeActor->ExecuteNode();
	}
	else if(Parameters[0].VariableNodeActor)
	{
		AVariableNodeActor* VariableCheck = Manager->GetVariableNode(Parameters[0].VariableNodeActor->GetVariableName());

		if(!VariableCheck) //Undeclared Variable
			{
			ErrorMessage = "No such variable called " + Parameters[0].VariableNodeActor->GetVariableName() + " found within the program.";
			return true;
			}
	}
	else
	{
		ErrorMessage = "Parameters Missing";
		return true;
	}

	return false;
}

void APrintNode::DisplayText()
{
	TextComponentMessage = "Print( ";

	if(Parameters[0].FunctionNodeActor)
	{
		TextComponentMessage += Parameters[0].FunctionNodeActor->GetTextComponentMessage() + " )";
	}else if(Parameters[0].VariableNodeActor)
	{
		TextComponentMessage += Parameters[0].VariableNodeActor->GetTextComponentMessage() + " )";
	}
	else
	{
		TextComponentMessage += ")";
	}

	NodeTextComponent->SetText(FText::FromString(TextComponentMessage));
}
