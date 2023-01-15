// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgramExecutionUI.h"

#include "Nodes/FunctionNode.h"

void UProgramExecutionUI::DisplayProgram(AFunctionNode* NodeToAdd)
{
	ProgramExecutionString = ProgramExecutionString + NodeToAdd->GetTextComponentMessage() + ";" + LINE_TERMINATOR;

	ExecutionTextBlock->SetText(FText::FromString(ProgramExecutionString));
}

void UProgramExecutionUI::ClearLog()
{
	ProgramExecutionString = "";
	ExecutionTextBlock->SetText(FText::FromString(ProgramExecutionString));
}
