// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionNode.h"

#include "VariableNodeActor.h"
#include "HonoursProject/NodeConsoleManager.h"

AFunctionNode::AFunctionNode()
{
	Parameter1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Parameter 1 Mesh"));
	Parameter1Mesh->SetupAttachment(RootComponent);

	
	Parameter2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Parameter 2 Mesh"));
	Parameter2Mesh->SetupAttachment(RootComponent);
}

void AFunctionNode::BeginPlay()
{
	Super::BeginPlay();
	Parameter1Mesh->OnComponentBeginOverlap.AddDynamic(this,&AFunctionNode::OnParameterOverlap);
	Parameter2Mesh->OnComponentBeginOverlap.AddDynamic(this,&AFunctionNode::OnParameterOverlap);
}

void AFunctionNode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AFunctionNode::ReturnValue(FString& TextReturnValue, double& NumberReturnValue)
{
	
	TextReturnValue = WordReturn;
	NumberReturnValue = NumberReturn;
}

FString AFunctionNode::GetWordReturnValue()
{
	return WordReturn;
}

double AFunctionNode::GetNumberReturnValue()
{
	return NumberReturn;
}

AActor* AFunctionNode::GetParameter(int Index)
{
	if(Index < Parameters.Num())
	{
		if(Parameters[Index].VariableNodeActor)
		{
			return Parameters[Index].VariableNodeActor;
		}
		else
		{
			return Parameters[Index].FunctionNodeActor;
		}
	}
	else
	{
		return nullptr;
	}
}

bool AFunctionNode::IsParameterSuitable(int ParameterNumber, AActor* NodeToSet)
{
	AVariableNodeActor* VariableNode = Cast<AVariableNodeActor>(NodeToSet); //See if the parameter trying to be added is a variable node.
	AFunctionNode* FunctionNode = Cast<AFunctionNode>(NodeToSet); //See if the parameter trying to be added it a function node.
	//Each parameter stores what data types it accepts, check that this parameter is of one of those types.
	bool ValidDataType = false;
	
if(VariableNode)
{
	for(int i = 0; i < Parameters[ParameterNumber].ValidDataTypes.Num();i++) //Loop through the array
	{
		if(Parameters[ParameterNumber].ValidDataTypes[i] == VariableNode->GetDataType()) //Check that the parameters are of the correct type.
		{
			ValidDataType = true;
		}
	}
}else if(FunctionNode && !Parameters[ParameterNumber].VariableSlot)
{
	for(int i = 0; i < Parameters[ParameterNumber].ValidDataTypes.Num();i++) //Loop through the array
		{
		if(Parameters[ParameterNumber].ValidDataTypes[i] == FunctionNode->ReturnType) //Check that the parameters are of the correct type.
			{
			ValidDataType = true;
			}
		}
}
else //Invalid type
{
		ErrorMessage = Parameters[ParameterNumber].ParameterName + " Must Receive A Data Type Node As Input";
		Manager->GetConsole()->AddToLog(ErrorMessage);
		return false; //Break out, Incorrect Data type
}
	
	
	if(!ValidDataType) //If it is of an invalid type
	{
		if(VariableNode){ErrorMessage = EnumManager::ConvertDataTypeToString(VariableNode->GetDataType()) + " Is Not A Valid Type For " + Parameters[ParameterNumber].ParameterName;}
		if(FunctionNode) {ErrorMessage = EnumManager::ConvertDataTypeToString(FunctionNode->ReturnType) + " Is Not A Valid Type For " + Parameters[ParameterNumber].ParameterName;}	
		Manager->GetConsole()->AddToLog(ErrorMessage);
		return false; //Break out, incorrect data type.
	}

	

	//Parameters[ParameterNumber].ActorComponent = NodeToSet;
	if(VariableNode)
	{
		Parameters[ParameterNumber].VariableNodeActor = VariableNode;
		Parameters[ParameterNumber].FunctionNodeActor = nullptr;
		Parameters[ParameterNumber].CurrentParameterDataType = VariableNode->GetDataType();
		ErrorMessage = "Successfully Set " + Parameters[ParameterNumber].ParameterName + " to " + VariableNode->GetVariableValue();
		//Manager->GetConsole()->AddToLog(ErrorMessage); // The variable is suitable to be used
	}
	if(FunctionNode)
	{
		Parameters[ParameterNumber].FunctionNodeActor = FunctionNode;
		Parameters[ParameterNumber].VariableNodeActor = nullptr;
		Parameters[ParameterNumber].CurrentParameterDataType = FunctionNode->ReturnType;
		ErrorMessage = "Successfully Set " + Parameters[ParameterNumber].ParameterName + " to " + FunctionNode->GetTextComponentMessage();
		//Manager->GetConsole()->AddToLog(ErrorMessage);
	}
	return true; //Return true, this variable can be added as a parameter.
}

void AFunctionNode::OnParameterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	float ParamNumber = -5;
	if(OverlappedComponent == Parameter1Mesh)
	{
		ParamNumber = 0;
	}
	else if(OverlappedComponent == Parameter2Mesh)
	{
		ParamNumber = 1;
	}
	
	if(ParamNumber >= 0)
	{
		if(OtherActor->IsA(AVariableNodeActor::StaticClass()) || OtherActor->IsA(AFunctionNode::StaticClass()))
		{
			AddParameter(ParamNumber,OtherActor);
		}
	}
}

void AFunctionNode::ExecuteNode()
{

}

bool AFunctionNode::IsThereCompileError()
{
	return false;
}


void AFunctionNode::AddParameter(int ParameterNumber, AActor* NodeToSet)
{
			if(IsParameterSuitable(ParameterNumber,NodeToSet)) //If the parameter is found to be suitable
				{
				//Parameters[ParameterNumber].ActorComponent = NodeToSet; //Store the actor
				//NodeToSet->AttachToComponent(NodeStaticMesh,FAttachmentTransformRules::SnapToTargetNotIncludingScale); //Attach the parameter to this node.
				UPrimitiveComponent* Comp = Cast<UPrimitiveComponent>(NodeToSet);
				if(Comp)
				{
					//Comp->SetSimulatePhysics(false); //Disable the physics.
				}
				DisplayText(); //Update the text to show the new variable.
				}
			else
			{
				Manager->GetConsole()->AddToLog(ErrorMessage);
			}
		
	
}
