// Fill out your copyright notice in the Description page of Project Settings.


#include "WhileLoopNode.h"

#include "VariableNodeActor.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AWhileLoopNode::AWhileLoopNode()
{
	ReturnType = NodeDataTypes::Unassigned;


	AttachmentBox = CreateDefaultSubobject<UBoxComponent>("Attachment Box");
	AttachmentBox->SetupAttachment(NodeStaticMesh);

	

}

void AWhileLoopNode::BeginPlay()
{
	Super::BeginPlay();
	Parameter2Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Parameter2Mesh->SetHiddenInGame(true);
	GetWorld()->GetTimerManager().SetTimer(Ticker,this,&AWhileLoopNode::CheckCodeBlock,0.25f,true,0.25f);
}

void AWhileLoopNode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AWhileLoopNode::ExecuteNode()
{
	FString StringReturn;
	double DoubleReturn;
	if(Parameters[0].FunctionNodeActor)
	{
		Parameters[0].FunctionNodeActor->ExecuteNode();
		Parameters[0].FunctionNodeActor->ReturnValue(StringReturn,DoubleReturn);
	}else if( Parameters[0].VariableNodeActor)
	{
		StringReturn = Manager->GetVariableNode(Parameters[0].VariableNodeActor->GetVariableName())->GetVariableValue();
		//StringReturn = Parameters[0].VariableNodeActor->GetVariableValue();
	}
	

	bool bWhileLoopReachedEnd = false; 

	//To prevent the player creating an infinite loop, this while loop node will use a large for loop beneath the hood
	for(int i = 0; i < 5000; i++)
	{
		for(int j = 0; j < CodeBlock.Num();j++)
		{
			CodeBlock[j]->ExecuteNode();
		}

		if(Parameters[0].FunctionNodeActor)
		{
			Parameters[0].FunctionNodeActor->ExecuteNode();
			Parameters[0].FunctionNodeActor->ReturnValue(StringReturn,DoubleReturn);
		}else if( Parameters[0].VariableNodeActor)
		{
			StringReturn = Manager->GetVariableNode(Parameters[0].VariableNodeActor->GetVariableName())->GetVariableValue();
			//StringReturn = Parameters[0].VariableNodeActor->GetVariableValue();
		}

		if(StringReturn != "true")
		{
			//If the condition is no longer true, the while loop would end at this point so break out of this for loop
			bWhileLoopReachedEnd = true;
			break;
		}
	}

	//If the for loop ran its course without the condition becoming false, assume an infinite loop. None of the questions in the game require this much looping so something has went wrong.
	if(!bWhileLoopReachedEnd)
	{
		bPotentialInfiniteLoop = true;
	}
	
	
	GEngine->AddOnScreenDebugMessage(3,10.0f,FColor::Yellow,TEXT("Ended While Loop"));
}

bool AWhileLoopNode::IsThereCompileError()
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

void AWhileLoopNode::DisplayText()
{
	TextComponentMessage = "While ";
	
	if(Parameters[0].FunctionNodeActor)
	{
		TextComponentMessage = TextComponentMessage + " (" + Parameters[0].FunctionNodeActor->GetTextComponentMessage() + " )";
	}else if(Parameters[0].VariableNodeActor)
	{
		TextComponentMessage = TextComponentMessage +Parameters[0].VariableNodeActor->GetVariableName();
	}
	else
	{
		TextComponentMessage =TextComponentMessage + "()";
	}
	
	NodeTextComponent->SetText(FText::FromString(TextComponentMessage));
}

void AWhileLoopNode::CheckCodeBlock()
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
			
			AFunctionNode* CurrentNodeActor = CurrentAttachedNode;

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
