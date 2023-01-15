// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumManager.h"
#include "GameFramework/Actor.h"
#include "LocalVariableNode.generated.h"

UCLASS()
class HONOURSPROJECT_API ALocalVariableNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocalVariableNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The data type of this Variable.
	NodeDataTypes VariableDataType = NodeDataTypes::Unassigned;

	FString VariableValue;
	
	class USceneComponent* SceneComponent;
	
	class UStaticMeshComponent* VariableMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDataType(NodeDataTypes TypeToSet);
	
	NodeDataTypes GetDataType();

	void SetVariableValue(FString ValueToSet);

	FString GetVariableValue();
	

};
