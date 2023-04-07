// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Door StaticMesh
	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("DoorSM"),false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshFinder(TEXT("/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube"));
	
	if(MeshFinder.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshFinder.Object);
	}
	MeshComponent->SetRelativeScale3D(FVector(0.25f,2.0f,3.5f));
	RootComponent = MeshComponent;
	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->startRotation = this->GetActorRotation();
	
	if(this->isOpen)
	{
		if(this->WaitTime > 0)
		{
			WaitTime -= DeltaTime;
			return;
		}

		if(timeElapsed < lerpDuration)
		{

			FRotator newRotator = FMath::Lerp(startRotation, targetRotator, timeElapsed / lerpDuration);
		
			this->SetActorRotation(newRotator);

			timeElapsed += DeltaTime;
		}
	}
}

void ADoor::TranslateDoor()
{
	this->isOpen = true;
}




