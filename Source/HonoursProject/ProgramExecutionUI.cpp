// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgramExecutionUI.h"

#include "Components/Button.h"
#include "Nodes/FunctionNode.h"

void UProgramExecutionUI::NativeConstruct()
{
	Super::NativeConstruct();

	ClearLogButton->OnClicked.AddDynamic(this,&UProgramExecutionUI::ClearLog);

	UndoButton->OnClicked.AddDynamic(this,&UProgramExecutionUI::Undo);
}

void UProgramExecutionUI::DisplayProgram(AFunctionNode* NodeToAdd)
{
	ProgramExecutionString = ProgramExecutionString + NodeToAdd->GetTextComponentMessage() + ";" + LINE_TERMINATOR;

	ExecutionTextBlock->SetText(FText::FromString(ProgramExecutionString));
}

void UProgramExecutionUI::ClearLog()
{
	ProgramExecutionString = "";
	ExecutionTextBlock->SetText(FText::FromString(ProgramExecutionString));
	Manager->ClearProgram();
}

void UProgramExecutionUI::SetManager(AProgramManager* ProgramToSet)
{
	Manager =  ProgramToSet;
}

void UProgramExecutionUI::Undo()
{
	Manager->Undo();
}

