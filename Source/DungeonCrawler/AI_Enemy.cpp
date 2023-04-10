// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Enemy.h"



// Sets default values
AAI_Enemy::AAI_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SM = CreateDefaultSubobject<UStaticMeshComponent>(FName("SM"));
	this->SM->SetupAttachment(RootComponent);

	this->SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	this->SphereCollider->InitSphereRadius(150.0f);
	this->SphereCollider->SetGenerateOverlapEvents(true);
	this->SphereCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	this->SphereCollider->SetupAttachment(SM);
	
	this->SphereCollider->OnComponentBeginOverlap.AddDynamic(this,&AAI_Enemy::OnOverlapBegin);
	
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

	MoveTo();
}

// Called to bind functionality to input
void AAI_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAI_Enemy::MoveTo()
{
	AEnemyController* EnemyController = Cast<AEnemyController>(GetController());

	EnemyController->MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(),30.f);
}

void AAI_Enemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADungeonCrawlerCharacter* player = Cast<ADungeonCrawlerCharacter>(OtherActor);
	
	if(player != nullptr && OtherActor != this && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Apply Damage"));
		OtherActor->TakeDamage(damage,FDamageEvent(UDamageType::StaticClass()),GetWorld()->GetFirstPlayerController(),this);
	}
}



