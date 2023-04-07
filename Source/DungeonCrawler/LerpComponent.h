// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LerpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLER_API ULerpComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULerpComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	float timeElapsed = 0;
	AActor* Parent = nullptr;
	FRotator StartRotation;
 
	UPROPERTY(EditAnywhere,Category=Lerp, Meta=(MakeEditWidget = true))
	FRotator targetRotator;
	
	UPROPERTY(EditAnywhere,Category=Lerp)
	float lerpDuration = 3;
	UPROPERTY(EditAnywhere,Category=Lerp)
	float WaitTime = 3;
};
