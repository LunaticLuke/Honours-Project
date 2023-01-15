// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateVariableUI.h"




void UCreateVariableUI::SetupButtons(ACreateVariableMachine* Machine)
{
	SelectString->MachineRef = Machine;
	SelectBool->MachineRef = Machine;
	SelectInt->MachineRef = Machine;
	SelectFloat->MachineRef = Machine;
	SelectChar->MachineRef = Machine;
}


