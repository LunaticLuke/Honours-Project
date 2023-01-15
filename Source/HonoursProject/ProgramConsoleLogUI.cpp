// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgramConsoleLogUI.h"

void UProgramConsoleLogUI::AddOutput(FString LineToAdd)
{
	ProgramLogString = ProgramLogString + LineToAdd + LINE_TERMINATOR;
	LogTextBlock->SetText(FText::FromString(ProgramLogString));
}

void UProgramConsoleLogUI::ClearLog()
{
	ProgramLogString = "";
	LogTextBlock->SetText(FText::FromString(ProgramLogString));
}
