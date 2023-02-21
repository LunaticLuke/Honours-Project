// Fill out your copyright notice in the Description page of Project Settings.


#include "ForLoopNode.h"

#include "VariableNodeActor.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AForLoopNode::AForLoopNode()
{
	ReturnType = NodeDataTypes::Unassigned;


	AttachmentBox = CreateDefaultSubobject<UBoxComponent>("Attachment Box");
	AttachmentBox->SetupAttachment(NodeStaticMesh);

	
	
}

void AForLoopNode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(Ticker,this,&AForLoopNode::CheckCodeBlock,0.25f,true,0.25f);
	Parameter2Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Parameter2Mesh->SetHiddenInGame(true);
}

void AForLoopNode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AForLoopNode::ExecuteNode()
{
	FString StringReturn;
	double DoubleReturn = 0;
	
	if(Parameters[0].FunctionNodeActor)
	{
		Parameters[0].FunctionNodeActor->ExecuteNode();
		Parameters[0].FunctionNodeActor->ReturnValue(StringReturn,DoubleReturn);
	}else if( Parameters[0].VariableNodeActor)
	{
		DoubleReturn = Manager->GetVariableNode(Parameters[0].VariableNodeActor->GetVariableName())->GetNumberValue();
		//DoubleReturn = Parameters[0].VariableNodeActor->GetNumberValue();
	}

	//Loop for however many times the attached variable says it should
	for(int i = 0; i < DoubleReturn;i++)
	{
		//GEngine->AddOnScreenDebugMessage(i,10.0f,FColor::Cyan,TEXT("Ran Loop"));
		for(int j = 0; j < CodeBlock.Num();j++)
		{
			CodeBlock[j]->ExecuteNode();
		}
	}
}

bool AForLoopNode::IsThereCompileError()
{
	for(int i = 0; i < Parameters.Num();i++)
	{
		if(Parameters[i].FunctionNodeActor)
		{
			if(Parameters[i].FunctionNodeActor->IsThereCompileError())
			{
				ErrorMessage = Parameters[i].FunctionNodeActor->GetErrorMessage();
				return true;
			}
			//Parameters[i].FunctionNodeActor->ExecuteNode();
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

	for(int i = 0; i < CodeBlock.Num();i++)
	{
		if(CodeBlock[i]->IsThereCompileError())
		{
			ErrorMessage = CodeBlock[i]->GetErrorMessage();
			return true;
		}
	}

	return false;
}

void AForLoopNode::DisplayText()
{
	TextComponentMessage = "Loop Amount: ";
	
	if(Parameters[0].FunctionNodeActor)
	{
		TextComponentMessage = TextComponentMessage + " (" + Parameters[0].FunctionNodeActor->GetTextComponentMessage() + " )";
	}else if(Parameters[0].VariableNodeActor)
	{
		TextComponentMessage = TextComponentMessage +Parameters[0].VariableNodeActor->GetVariableName();
	}
	else
	{
		TextComponentMessage =TextComponentMessage + "";
	}
	
	NodeTextComponent->SetText(FText::FromString(TextComponentMessage));
}

void AForLoopNode::CheckCodeBlock()
{
	if(!bAddedToProgram)
	{
		for(int i = 0; i < CodeBlock.Num();i++)
		{
			CodeBlock[i]->bWithinFunction = false;
		}
		CodeBlock.Empty();
		if(CurrentAttachedNode)
		{
			CodeBlock.Empty();
			AFunctionNode* CurrentNodeActor = CurrentAttachedNode;
			CurrentNodeActor->bWithinFunction = true;
			
			CodeBlock.Push(CurrentNodeActor);
			while(CurrentNodeActor != nullptr)
			{
				CurrentNodeActor = CurrentNodeActor->CurrentAttachedNode;
				if(CurrentNodeActor)
				{
					CurrentNodeActor->bWithinFunction = true;
					CodeBlock.Push(CurrentNodeActor);
				}
			}
			
		}
	}
}
