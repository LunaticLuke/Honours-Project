// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectDataTypeButton.h"

#include "CreateVariableMachine.h"
#include "CreateVariableUI.h"

USelectDataTypeButton::USelectDataTypeButton()
{
	OnClicked.AddDynamic(this,&USelectDataTypeButton::ChooseDataType);
}

void USelectDataTypeButton::ChooseDataType()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Button Method"));
	MachineRef->SetDataType(TypeToSelect);
}
