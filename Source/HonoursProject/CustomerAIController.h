// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "CustomerAIController.generated.h"



/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API ACustomerAIController : public AAIController
{
	GENERATED_BODY()


public:
	void MoveCustomer(FVector LocationToMoveTo);
};
