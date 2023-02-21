// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HonoursProject/ProgramManager.h"
#include "NodeActor.generated.h"




UCLASS()
class HONOURSPROJECT_API ANodeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeActor();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsHeld = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FString ErrorMessage;

	FString TextComponentMessage;
	
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    class UStaticMeshComponent* NodeStaticMesh;
	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* NodeTextComponent;

	virtual void DisplayText();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddForce(FVector Location, FVector Force);

	void ConfigurePhysics(bool PhysicsEnabled);
	UPROPERTY(BlueprintReadWrite)
	bool bAddedToProgram = false;
	
	FString GetErrorMessage();
	UPROPERTY(EditAnywhere);
	AProgramManager* Manager;

	FString GetTextComponentMessage();

};
