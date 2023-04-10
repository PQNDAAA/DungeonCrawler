// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"
// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("TrapSM"),false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshFinder(TEXT("/Game/Mesh/Trap_fbx.Trap_fbx"));

	if(MeshFinder.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshFinder.Object);
	}
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);

	SetActorEnableCollision(true);

	this->SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	this->SphereCollider->InitSphereRadius(150.0f);
	this->SphereCollider->SetGenerateOverlapEvents(true);
	this->SphereCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	this->SphereCollider->SetupAttachment(MeshComponent);
	
	this->SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ATrap::OnOverlapBegin);
	
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();

	damage = FMath::RandRange(10,35);
	
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	ADungeonCrawlerCharacter* player = Cast<ADungeonCrawlerCharacter>(OtherActor);

	if(player != nullptr && OtherActor != this && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Apply Damage"));
		OtherActor->TakeDamage(damage,FDamageEvent(UDamageType::StaticClass()),GetWorld()->GetFirstPlayerController(),this);
		
	}
}



