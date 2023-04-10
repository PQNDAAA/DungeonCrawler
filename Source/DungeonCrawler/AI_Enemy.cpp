// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Enemy.h"


// Sets default values
AAI_Enemy::AAI_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->MaxWalkSpeed = this->speedMovement;

	this->SM = CreateDefaultSubobject<UStaticMeshComponent>(FName("SM"));
	this->SM->SetupAttachment(RootComponent);

	this->CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleColliderDamage"));
	this->CapsuleCollider->InitCapsuleSize(70.f, 96.0f);
	this->CapsuleCollider->SetGenerateOverlapEvents(true);
	this->CapsuleCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	this->CapsuleCollider->SetupAttachment(SM);

	this->SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereColliderWalk"));
	this->SphereCollider->SetSphereRadius(150.f);
	this->SphereCollider->SetGenerateOverlapEvents(true);
	this->SphereCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	this->SphereCollider->SetupAttachment(RootComponent);
	
	this->CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this,&AAI_Enemy::OnOverlapBeginDamage);
	
	this->SphereCollider->OnComponentBeginOverlap.AddDynamic(this,&AAI_Enemy::OnOverlapBeginWalk);
	this->SphereCollider->OnComponentEndOverlap.AddDynamic(this,&AAI_Enemy::OnOverlapEndWalk);
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

	AEnemyController* EnemyController = Cast<AEnemyController>(GetController());

	if(!isChasingPlayer)
	{
		if(!hasPath)
		{
			targetPositionToMove = UBFL_Main::GetRandomReachablePoint(this->GetActorLocation(),500);
			EnemyController->MoveToLocation(targetPositionToMove,-1);
			hasPath = true;
		}

		if(EnemyController->GetPathFollowingComponent()->GetStatus() == EPathFollowingStatus::Idle && hasPath)
		{
			hasPath = false;
		}
	}

	//NOTE FOR ME
	//if(!hasPath)
	//{
	//	targetPosition = UBFL_Main::RandomWalk(this->GetActorLocation(),70);
	//	this->SetActorLocation(targetPosition,false);
	//	hasPath = true;
	//}

	//if(this->GetActorLocation().Equals(targetPosition,0.01f) && hasPath)
	//{
	//	hasPath = false;
	//}
	
}

// Called to bind functionality to input
void AAI_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Function to move the enemy to player
void AAI_Enemy::MoveTo()
{
	AEnemyController* EnemyController = Cast<AEnemyController>(GetController());

	EnemyController->MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(),30.f);
}

//Overlap Begin to inflict damage 
void AAI_Enemy::OnOverlapBeginDamage(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADungeonCrawlerCharacter* player = Cast<ADungeonCrawlerCharacter>(OtherActor);
	
	if(player != nullptr && OtherActor != this && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Apply Damage"));
		OtherActor->TakeDamage(damage,FDamageEvent(UDamageType::StaticClass()),GetWorld()->GetFirstPlayerController(),this);
	}
}

//Overlap Begin to walk to....
void AAI_Enemy::OnOverlapBeginWalk(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADungeonCrawlerCharacter* player = Cast<ADungeonCrawlerCharacter>(OtherActor);

	if(player != nullptr && OtherActor != this && OtherComp)
	{
		MoveTo();
		isChasingPlayer = true;
		hasPath = false;
	}
}

//Overlap End when the player leaves the sphere collider
void AAI_Enemy::OnOverlapEndWalk(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADungeonCrawlerCharacter* player = Cast<ADungeonCrawlerCharacter>(OtherActor);

	if(player != nullptr && OtherActor != this && OtherComp)
	{
		isChasingPlayer = false;
	}
}

//Take Damage / UE5 FUNCTION SYSTEM
float AAI_Enemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	this->health = UBFL_Main::ReduceHealth(DamageAmount,this->health);
	UBFL_Main::isPlayerDead(this->health) ? this->K2_DestroyActor(), true : false;

	return DamageAmount;
}





