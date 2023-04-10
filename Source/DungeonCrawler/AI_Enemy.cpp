// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Enemy.h"

#include "AIController.h"
#include "EnemyController.h"

// Sets default values
AAI_Enemy::AAI_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SM = CreateDefaultSubobject<UStaticMeshComponent>(FName("SM"));
	this->SM->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AAI_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTo(this->destinationActor);
}

// Called to bind functionality to input
void AAI_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAI_Enemy::MoveTo(AActor* targetActor)
{
	AEnemyController* EnemyController = Cast<AEnemyController>(GetController());

	EnemyController->MoveToActor(targetActor,5.f,false);
}

void AAI_Enemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->TakeDamage(this->damage,FDamageEvent(UDamageType::StaticClass()),GetWorld()->GetFirstPlayerController(),this);
}



