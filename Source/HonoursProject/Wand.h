// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRInteractionAPI.h"
#include "GameFramework/Actor.h"
#include "Wand.generated.h"

UCLASS()
class HONOURSPROJECT_API AWand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* WandMeshComponent;
	UPROPERTY(EditAnywhere)
	class UArrowComponent* WandOrigin;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
