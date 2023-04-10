// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DungeonCrawler/Character/DungeonCrawlerCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "AI_Enemy.generated.h"

UCLASS()
class DUNGEONCRAWLER_API AAI_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Enemy();

	//Sphere Collider 
	UPROPERTY(VisibleAnywhere, Category="Sphere")
	UStaticMeshComponent* SM;

	UPROPERTY(EditAnywhere, Category="Actor")
	AActor* destinationActor;

	UPROPERTY(EditAnywhere, Category="Damage")
	float damage = 10.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void MoveTo(AActor* targetActor);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

};
