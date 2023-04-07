// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "LerpComponent.h"

// Sets default values for this component's properties
ULerpComponent::ULerpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	Parent = GetOwner();
}


// Called when the game starts
void ULerpComponent::BeginPlay()
{
	Super::BeginPlay();

	this->StartRotation = GetComponentRotation();
}


// Called every frame
void ULerpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ADoor* door = Cast<ADoor>(Parent->GetOwner());

	if(door->isOpen)
	{
		if(this->WaitTime > 0)
		{
			WaitTime -= DeltaTime;
			return;
		}

		if(timeElapsed < lerpDuration)
		{

			FRotator newRotator = FMath::Lerp(StartRotation, targetRotator, timeElapsed / lerpDuration);
		
			Parent->SetActorRotation(newRotator);

			timeElapsed += DeltaTime;
		}
	}
}

