// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "DungeonCrawler/Character/DungeonCrawlerCharacter.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

	/**Default value to inflict damage*/ 
	UPROPERTY(EditAnywhere, Category="Stats")
	float damage = 10.0f;

	//Static Mesh
	UPROPERTY(EditAnywhere, Category="StaticMesh")
	UStaticMeshComponent* MeshComponent;

	//Sphere Collider 
	UPROPERTY(VisibleAnywhere, Category="Sphere")
	USphereComponent* SphereCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	

};
