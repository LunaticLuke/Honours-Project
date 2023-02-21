// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionNode.h"
#include "ForLoopNode.generated.h"


class UBoxComponent;
/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API AForLoopNode : public AFunctionNode
{
	GENERATED_BODY()

	AForLoopNode();
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void ExecuteNode() override;

	virtual bool IsThereCompileError() override;

	virtual void DisplayText() override;

protected:

	void CheckCodeBlock();

	
	//Is an else attached to this if statement
	bool bElseStatement = false;

	FVector StartingBoxLocation; 
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	UBoxComponent* AttachmentBox;

	//Stores the nodes within the if block
	UPROPERTY(EditAnywhere)
	TArray<AFunctionNode*> CodeBlock;
	
	
	float NodeHeight;

	FTimerHandle Ticker;
};
