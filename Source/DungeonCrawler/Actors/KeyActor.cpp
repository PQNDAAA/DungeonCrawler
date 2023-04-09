// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyActor.h"

// Sets default values
AKeyActor::AKeyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("KeySM"),false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshFinder(TEXT("/Game/Mesh/Key.Key"));

	if(MeshFinder.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshFinder.Object);
	}
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);

	SetActorEnableCollision(true);

}

// Called when the game starts or when spawned
void AKeyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

