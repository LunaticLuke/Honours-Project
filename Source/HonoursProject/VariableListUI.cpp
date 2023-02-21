// Fill out your copyright notice in the Description page of Project Settings.


#include "VariableListUI.h"
#include "Nodes/VariableNodeActor.h"

void UVariableListUI::DisplayVariables(AVariableNodeActor* VariableToAdd)
{
	VariableListString = VariableListString + EnumManager::ConvertDataTypeToString(VariableToAdd->GetDataType()) + " " + VariableToAdd->GetVariableName() + " = ";

	if(VariableToAdd->GetDataType() == NodeDataTypes::String || VariableToAdd->GetDataType() == NodeDataTypes::Char || VariableToAdd->GetDataType() == NodeDataTypes::Bool)
	{
		VariableListString = VariableListString + VariableToAdd->GetVariableValue() + LINE_TERMINATOR;
	}
	else
	{
		VariableListString = VariableListString + FString::SanitizeFloat(VariableToAdd->GetNumberValue()) + LINE_TERMINATOR;
	}
	VariableText->SetText(FText::FromString(VariableListString));
}

void UVariableListUI::ClearVariableLog()
{
	VariableText->SetText(FText::FromString(VariableListString));
}