// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionNode.h"
#include "RelationalOperatorNode.generated.h"


UENUM()
enum class ERelationalOperators
{
	LessThan,
	LessThanEqualTo,
	GreaterThan,
	GreaterThanEqualTo,
	EqualTo,
	NotEqualTo
};
/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API ARelationalOperatorNode : public AFunctionNode
{
	GENERATED_BODY()

ARelationalOperatorNode();

public:
	ERelationalOperators GetRelationalOperator();
protected:
	virtual void BeginPlay() override;
	
	virtual void ExecuteNode() override;

	virtual bool IsThereCompileError() override;

	virtual void DisplayText() override;
	
	UPROPERTY(EditAnywhere)
	ERelationalOperators RelationalOperator;

	
	
	
};
