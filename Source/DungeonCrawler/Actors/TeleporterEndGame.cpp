// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleporterEndGame.h"

// Sets default values
ATeleporterEndGame::ATeleporterEndGame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize the sphere collider
	this->SphereCollider = CreateDefaultSubobject<USphereComponent>(FName("SphereCollider"),false);
	this->SphereCollider->InitSphereRadius(150.0f);
	this->SphereCollider->SetGenerateOverlapEvents(true);
	this->SphereCollider->SetCollisionProfileName(FName("OverlapAllDynamic"));
	this->SphereCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATeleporterEndGame::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleporterEndGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporterEndGame::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


