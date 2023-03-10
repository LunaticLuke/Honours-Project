// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomerManager.generated.h"

class ACustomer;
class UCustomerRequest;
class ATargetPoint;
class UBoxComponent;
class UCustomerRequestUI;
class UWidgetComponent;

UCLASS()
class HONOURSPROJECT_API ACustomerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	ACustomer* Customer;
	
	UPROPERTY(EditAnywhere)
	TArray<UCustomerRequest*> Requests;

	int CurrentRequestNumber = 0;

	void SpawnCustomer();
	UPROPERTY(EditAnywhere)
	UBoxComponent* PotionTriggerZone;
	UFUNCTION()
	virtual void OnParameterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UPROPERTY(EditAnywhere)
	UWidgetComponent* WidgetComponent;
	
	UCustomerRequestUI* RequestUIClass;

	int ServedCustomers = 0;
	
	bool bCustomerCanEnter = false;

	bool bCustomerAlreadyInShop = false;
	
	FTimerHandle Ticker;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int GetServedCustomers();

	void AllowCustomers(bool bAllow);
};
