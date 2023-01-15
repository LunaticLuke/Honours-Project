// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionNode.h"
#include "AssignmentNode.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API AAssignmentNode : public AFunctionNode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	
	virtual void ExecuteNode() override;

	virtual bool IsThereCompileError() override;

	virtual void DisplayText() override;
};
