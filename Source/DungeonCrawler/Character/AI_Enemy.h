// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DungeonCrawler/Character/DungeonCrawlerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "DungeonCrawler/Controllers/EnemyController.h"
#include "Components/SphereComponent.h"
#include "DungeonCrawler/Library/BFL_Main.h"
#include "AI_Enemy.generated.h"

UCLASS()
class DUNGEONCRAWLER_API AAI_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Enemy();

	//StaticMeshComponent  
	UPROPERTY(VisibleAnywhere, Category="SM")
	UStaticMeshComponent* SM;

	//Capsule Collider 
	UPROPERTY(VisibleAnywhere, Category="Capsule")
	UCapsuleComponent* CapsuleCollider;

	//Sphere Collider
	UPROPERTY(VisibleAnywhere,Category="Sphere")
	USphereComponent* SphereCollider;

	//Damage
	UPROPERTY(EditAnywhere, Category="Damage System")
	float damage = 10.f;

	//Health
	UPROPERTY(EditAnywhere, Category="Health System")
	float health = 40.f;

	//Speed Movement "Walk"
	UPROPERTY(EditAnywhere, Category="Walk System")
	float speedMovement = 200.f;

	UPROPERTY()
	bool isChasingPlayer = false;

	UPROPERTY()
	bool hasRandomPath = false;

	//targetPosition if the AI has a random Path
	UPROPERTY()
	FVector targetPositionToMove;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser) override;

public:	

	//MoveToPlayer Function
	UFUNCTION()
	void MoveTo();

	UFUNCTION()
	void OnOverlapBeginDamage(class UPrimitiveComponent *OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapBeginWalk(class UPrimitiveComponent *OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEndWalk(class UPrimitiveComponent *OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	//Move Randomly
	UFUNCTION(BlueprintCallable, Category="Walk System")
	void MoveRandomly();
	
};
