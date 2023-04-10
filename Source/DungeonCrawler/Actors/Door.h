// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	//DoorSMComponent
	UPROPERTY(EditAnywhere,Category="Door")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere,Category="Door")
	bool isOpen = false;

	//Var for lerp
	UPROPERTY(EditAnywhere,Category=Lerp, Meta=(MakeEditWidget = true))
	FRotator targetRotator;
	UPROPERTY(EditAnywhere,Category=Lerp)
	float lerpDuration = 3;
	UPROPERTY(EditAnywhere,Category=Lerp)
	float WaitTime = 3;
	FRotator startRotation;
	float timeElapsed =0.f;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Open Door
	UFUNCTION(BlueprintCallable, Category="OpenDoor")
	void TranslateDoor();

};
