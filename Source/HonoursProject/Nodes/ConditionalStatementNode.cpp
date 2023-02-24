// Fill out your copyright notice in the Description page of Project Settings.


#include "ConditionalStatementNode.h"

#include "VariableNodeActor.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AConditionalStatementNode::AConditionalStatementNode()
{
	ReturnType = NodeDataTypes::Unassigned;


	AttachmentBox = CreateDefaultSubobject<UBoxComponent>("Attachment Box");
	AttachmentBox->SetupAttachment(NodeStaticMesh);

	
}

void AConditionalStatementNode::BeginPlay()
{
	Super::BeginPlay();
	NodeHeight = NodeStaticMesh->GetComponentScale().Z;
	GetWorld()->GetTimerManager().SetTimer(Ticker,this,&AConditionalStatementNode::CheckCodeBlock,0.25f,true,0.25f);
	Parameter2Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Parameter2Mesh->SetHiddenInGame(true);
	//Parameters.Pop();
}

void AConditionalStatementNode::Tick(float DeltaSeconds)
{

	
}

void AConditionalStatementNode::ExecuteNode()
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

	//If the bool condition returns true, execute all nodes within the if block.
	if(StringReturn == "true")
	{
		GEngine->AddOnScreenDebugMessage(0,5.0f,FColor::Cyan,TEXT("If Statement Is Running"));
		for(int i = 0; i < IfCodeBlock.Num();i++)
		{
			IfCodeBlock[i]->ExecuteNode();
		}
	}else
	{
		GEngine->AddOnScreenDebugMessage(0,5.0f,FColor::Cyan,TEXT("Else Statement Is Running"));
		if(StringReturn == "false" && bElseStatement)
		{
			for(int i = 0; i < ElseCodeBlock.Num();i++)
			{
				ElseCodeBlock[i]->ExecuteNode();
			}
		}
	}
}

bool AConditionalStatementNode::IsThereCompileError()
{
	
	if(Parameters[0].FunctionNodeActor)
	{
		if(Parameters[0].FunctionNodeActor->IsThereCompileError())
		{
			ErrorMessage = Parameters[0].FunctionNodeActor->GetErrorMessage();
			return true;
		}
			//Parameters[i].FunctionNodeActor->ExecuteNode();
		}
		else if(Parameters[0].VariableNodeActor)
		{
			AVariableNodeActor* VariableCheck = Manager->GetVariableNode(Parameters[0].VariableNodeActor->GetVariableName());

			if(!VariableCheck) //Undeclared Variable
				{
				ErrorMessage = "No such variable called " + Parameters[0].VariableNodeActor->GetVariableName() + " found within the program.";
				return true;
				}
		}
		else
		{
			ErrorMessage = "Parameters Missing";
			return true;
		}
	

	for(int i = 0; i < IfCodeBlock.Num();i++)
	{
		if(IfCodeBlock[i]->IsThereCompileError())
		{
			ErrorMessage = IfCodeBlock[i]->GetErrorMessage();
			return true;
		}
	}

	if(bElseStatement)
	{
		for(int i = 0; i < ElseCodeBlock.Num();i++)
		{
			if(ElseCodeBlock[i]->IsThereCompileError())
			{
				ErrorMessage = ElseCodeBlock[i]->GetErrorMessage();
				return true;
			}
		}
	}
	return false;
}

void AConditionalStatementNode::DisplayText()
{
	TextComponentMessage = "If ";
	
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

void AConditionalStatementNode::CheckCodeBlock()
{
	if(!bAddedToProgram)
	{
		for(int i = 0; i < IfCodeBlock.Num(); i++)
		{
			IfCodeBlock[i]->bWithinFunction = false;
		}
		IfCodeBlock.Empty();
		if(CurrentAttachedNode)
		{
			IfCodeBlock.Empty();
			AFunctionNode* CurrentNodeActor = CurrentAttachedNode;
			CurrentNodeActor->bWithinFunction = true;
		
			IfCodeBlock.Push(CurrentNodeActor);
			while(CurrentNodeActor != nullptr)
			{
				CurrentNodeActor = CurrentNodeActor->CurrentAttachedNode;
				if(CurrentNodeActor)
				{
					CurrentNodeActor->bWithinFunction = true;
					IfCodeBlock.Push(CurrentNodeActor);
				}
			}
			
		}
	}
	
}
