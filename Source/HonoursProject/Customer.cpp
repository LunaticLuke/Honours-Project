// Fill out your copyright notice in the Description page of Project Settings.


#include "Customer.h"

#include "CustomerAIController.h"
#include "Potion.h"
#include "Nodes/ArithmeticOperatorNode.h"
#include "Nodes/LogicalOperatorNode.h"
#include "Nodes/RelationalOperatorNode.h"
#include "Nodes/FunctionNode.h"
#include "Nodes/VariableNodeActor.h"
#include "Requests/CustomerRequest.h"

// Sets default values
ACustomer::ACustomer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    AIControllerClass = ACustomerAIController::StaticClass();
	
}

// Called when the game starts or when spawned
void ACustomer::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void ACustomer::AreRequestedVariablesFound()
{
	for (int i = 0; i < CurrentRequest->RequestedVariables.Num();i++)
	{
		FVariableRequest CurrentVariable = CurrentRequest->RequestedVariables[i];
		
		for(int j = 0; j < CurrentPotion->ProgramVariables.Num(); j++)
		{
			for(int x = 0; x < CurrentVariable.RequiredDataTypes.Num();x++)
			{
				if(CurrentVariable.RequiredDataTypes[x] == CurrentPotion->ProgramVariables[j]->GetDataType()) //Checking for correct data type
				{
					GEngine->AddOnScreenDebugMessage(-1,50.0f,FColor::Yellow,TEXT("Data Types Match"));
					if(!CurrentVariable.bSpecificName || CurrentVariable.RequiredName == CurrentPotion->ProgramVariables[j]->GetVariableName()) //Checking the name, if needed
					{
						GEngine->AddOnScreenDebugMessage(-1,50.0f,FColor::Yellow,TEXT("Name Match"));
						//Checking - if needed - the starting values match up
						if(!CurrentVariable.bSpecificStartingValue || CurrentVariable.RequiredNumberStartingValue == CurrentPotion->VariableData[j].StartingNumberValue || CurrentVariable.RequiredTextStartingValue == CurrentPotion->VariableData[j].StartingTextValue) 
						{
							GEngine->AddOnScreenDebugMessage(-1,50.0f,FColor::Yellow,TEXT("Starting Value Match"));
							if(!CurrentVariable.bSpecificEndingValue || CurrentVariable.RequiredNumberValue == CurrentPotion->VariableData[j].CurrentNumberValue || CurrentVariable.RequiredTextValue == CurrentPotion->VariableData[j].CurrentTextValue)
							{
								GEngine->AddOnScreenDebugMessage(-1,50.0f,FColor::Yellow,TEXT("Total Match"));
								CurrentRequest->RequestedVariables[i].bFoundWithinProgram = true;
							}
						}
					}
				}
			}
		}
	}
}



bool ACustomer::CheckVariableName(FString NameToCheck)
{
	for(int i = 0; i < CurrentPotion->VariableData.Num(); i++)
	{
		if(CurrentPotion->ProgramVariables[i]->GetVariableName() == NameToCheck)
		{
			return true;
		}
	}
	return false;
}

void ACustomer::CheckProgramExecution()
{
	for(int i = 0; i < CurrentRequest->RequestedFunctions.Num();i++)
	{
		FFunctionRequest CurrentNode = CurrentRequest->RequestedFunctions[i];
		for(int j = 0; j < CurrentPotion->ProgramArray.Num();j++)
		{
			if(CurrentNode.RequiredNodeType == CurrentPotion->ProgramArray[j]->GetClass())
			{
				if(!CurrentNode.bSpecificArithmeticOperator || CheckArithmeticOperator(CurrentPotion->ProgramArray[j],CurrentNode))
				{
					if(CurrentNode.RequestedParameters.Num() == 0 || CheckParameters(CurrentPotion->ProgramArray[j],CurrentNode))
					{
						CurrentRequest->RequestedFunctions[i].bFoundWithinProgram = true;
					}
				}
			}
		}
	}
}

bool ACustomer::CheckParameters(AFunctionNode* NodeToCheck, FFunctionRequest RequestToCheck)
{

	TArray<bool> ParamChecks;
	for(int i = 0; i < RequestToCheck.RequestedParameters.Num(); i++)
	{
		ParamChecks.Push(false);
	}
	
	
	for(int i = 0; i < RequestToCheck.RequestedParameters.Num();i++)
	{
		FParameterRequest CurrentParam = RequestToCheck.RequestedParameters[i];
		if(!CurrentParam.bSpecificParameterDataType || CurrentParam.TypeOfParameter == NodeToCheck->GetParameter(i)->GetClass())
		{
			if(!CurrentParam.bSpecificValue || CurrentParam.RequiredParamNumValue == GetParameterNumberValue(NodeToCheck,i) || CurrentParam.RequiredParamTextValue == GetParameterTextValue(NodeToCheck,i))
			{
				if(!CurrentParam.bSpecificLogicalOperatorTypeRequired || CheckLogicalOperator(NodeToCheck->GetParameter(i),RequestToCheck.RequestedParameters[i]))
				{
					if(!CurrentParam.bSpecificRelationalOperatorNodeRequired || CheckRelationalOperator(NodeToCheck->GetParameter(i),RequestToCheck.RequestedParameters[i]))
					{
						if(!CurrentParam.bSpecificParam1Value || CheckInnerParameter(NodeToCheck->GetParameter(i),0,CurrentParam.RequestedParam1NumValue,CurrentParam.RequestedParam1TextValue))
						{
							if(!CurrentParam.bSpecificParam2Value || CheckInnerParameter(NodeToCheck->GetParameter(i),1,CurrentParam.RequestedParam2NumValue,CurrentParam.RequestedParam2TextValue))
							{
								ParamChecks[i] = true;
							}
						}
					}
				}
			}
		}
	}


	for(int i = 0; i < ParamChecks.Num();i++)
	{
		if(!ParamChecks[i])
		{
			return false;
		}
	}
	return true;
}

bool ACustomer::CheckLogicalOperator(AActor* NodeToCheck, FParameterRequest ReqToCheck)
{
	if(Cast<ALogicalOperatorNode>(NodeToCheck))
	{
		if(Cast<ALogicalOperatorNode>(NodeToCheck)->GetLogicalOperator() == ReqToCheck.LogicalOperatorTypeRequired)
		{
			return true;
		}
	}
	return false;
}


bool ACustomer::CheckRelationalOperator(AActor* NodeToCheck, FParameterRequest ReqToCheck)
{
	if(Cast<ARelationalOperatorNode>(NodeToCheck))
	{
		if(Cast<ARelationalOperatorNode>(NodeToCheck)->GetRelationalOperator() == ReqToCheck.RelationalOperatorRequired)
		{
			return true;
		}
	}
	return false;
}

double ACustomer::GetParameterNumberValue(AFunctionNode* NodeToCheck, int Index)
{
	AActor* NodeParameter = NodeToCheck->GetParameter(Index);

	if(Cast<AVariableNodeActor>(NodeParameter))
	{
		return Cast<AVariableNodeActor>(NodeParameter)->GetNumberValue();
	}else
	{
		return Cast<AFunctionNode>(NodeParameter)->GetNumberReturnValue();
	}
}

FString ACustomer::GetParameterTextValue(AFunctionNode* NodeToCheck, int Index)
{
	AActor* NodeParameter = NodeToCheck->GetParameter(Index);

	if(Cast<AVariableNodeActor>(NodeParameter))
	{
		return Cast<AVariableNodeActor>(NodeParameter)->GetVariableValue();
	}else
	{
		return Cast<AFunctionNode>(NodeParameter)->GetWordReturnValue();
	}
}

bool ACustomer::CheckInnerParameter(AActor* NodeToCheck, int Index, double ValueToCheck, FString TextToCheck)
{
	AActor* ParamToCheck = nullptr;
	if(Cast<AFunctionNode>(NodeToCheck))
	{
		//First get the parameter of this node
		ParamToCheck = Cast<AFunctionNode>(NodeToCheck)->GetParameter(Index); 
		if(!ParamToCheck)
		{
			//Null pointer = invalid parameter slot, return false
			return false;
		}
	}
	//Initialise values to store param values.
	double NumberValue;
	FString TextValue;
	//Check if the param is a function or variable, if neither, exit out, something wrong.
	if(Cast<AFunctionNode>(ParamToCheck))
	{
		NumberValue = Cast<AFunctionNode>(ParamToCheck)->GetNumberReturnValue();
		TextValue = Cast<AFunctionNode>(ParamToCheck)->GetWordReturnValue();
		
	}else if(Cast<AVariableNodeActor>(ParamToCheck))
	{
		NumberValue = Cast<AVariableNodeActor>(ParamToCheck)->GetNumberValue();
		TextValue = Cast<AVariableNodeActor>(ParamToCheck)->GetVariableValue();
	}
	else
	{
		return false;
	}
	//if the number values are equal or the text values are, break out.
	if(NumberValue == ValueToCheck || TextValue == TextToCheck)
	{
		return true;
	}

	return false;
}

// Called every frame
void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACustomer::CheckArithmeticOperator(AFunctionNode* NodeToCheck, FFunctionRequest RequestToCheck)
{
	if(Cast<AArithmeticOperatorNode>(NodeToCheck))
	{
		if(Cast<AArithmeticOperatorNode>(NodeToCheck)->GetArithmeticOperatorType() == RequestToCheck.ArithmeticOperatorTypeRequired)
		{
			return true;
		}
	}

	return false;
}


// Called to bind functionality to input
void ACustomer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACustomer::MoveToCounter()
{

	Cast<ACustomerAIController>(GetController())->MoveCustomer(ServingPoint->GetActorLocation());
	
	
}

void ACustomer::MoveToExit()
{
	
	Cast<ACustomerAIController>(GetController())->MoveCustomer(ExitPoint->GetActorLocation());
	
}

void ACustomer::SetRequest(UCustomerRequest* RequestToSet)
{
	CurrentRequest = RequestToSet;
}

void ACustomer::SetPotion(APotion* PotionToSet)
{
	CurrentPotion = PotionToSet;
}

void ACustomer::VariableCheck()
{
	bool bCorrectPotion = true;
	AreRequestedVariablesFound();
	CheckProgramExecution();
	for(int i = 0; i < CurrentRequest->RequestedVariables.Num();i++)
	{
		if(!CurrentRequest->RequestedVariables[i].bFoundWithinProgram)
		{
			GEngine->AddOnScreenDebugMessage(-1,50.0f,FColor::Yellow,TEXT("Missing Variable"));
			bCorrectPotion = false;
		}
	}

	for(int i = 0; i < CurrentRequest->RequestedFunctions.Num();i++)
	{
		if(!CurrentRequest->RequestedFunctions[i].bFoundWithinProgram)
		{
			GEngine->AddOnScreenDebugMessage(-1,50.0f,FColor::Cyan,TEXT("Missing Node"));
			bCorrectPotion = false;
		}
	}

	if(bCorrectPotion)
	{
		GEngine->AddOnScreenDebugMessage(-1,50.0f,FColor::Cyan,TEXT("Correct"));
		MoveToExit();
	}
}

