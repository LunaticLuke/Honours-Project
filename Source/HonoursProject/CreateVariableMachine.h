// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumManager.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Nodes/VariableNodeActor.h"
#include "CreateVariableMachine.generated.h"


class UCreateVariableUI;
UCLASS()
class HONOURSPROJECT_API ACreateVariableMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACreateVariableMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	NodeDataTypes DataTypeToCreate = NodeDataTypes::Unassigned;

	FString VariableName = "";

	bool bNameAssigned = false;

	bool bStartingValueAssigned = false;

	bool bNumberVariable = false;

	FString VariableValue = "";

	double VariableNumberValue = 0;

	AVariableNodeActor* LastCreatedVariable;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	class UArrowComponent* SpawnLocation;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ConveyorBeltMachine;
	UPROPERTY(EditAnywhere)
	UWidgetComponent* CreateVariableUI;

	UCreateVariableUI* UIClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AVariableNodeActor> DefaultVariableNode;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateVariable();

	void SetDataType(NodeDataTypes TypeToAssign);

	void AddToVariableName(FString NameToAssign);

	void AddToVariableStartingValue(FString ValueToAssign, bool IsNumber);

	NodeDataTypes GetCurrentDataType();

	void Backspace();

	bool bChoosingVariableName = true;

	bool bChoosingVariableStartingValue = false;

	bool bCapsLock = false;

};
