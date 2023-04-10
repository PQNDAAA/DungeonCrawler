// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BFL_Main.generated.h"

UCLASS()
class DUNGEONCRAWLER_API UBFL_Main : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Add Actor in the player inventory 
	UFUNCTION(BlueprintCallable, Category="CharacterInventory")
	static void AddActorInventory(AActor* targetPlayer,AActor* actor, int32 quantity);

	//Reduce the entity health
	UFUNCTION(BlueprintCallable,Category="Health System")
	static float ReduceHealth(float damage,float health);

	//Function to check if the entity is dead or not 
	UFUNCTION(BlueprintCallable,Category="Health System")
	static bool isPlayerDead(float health);

	//Generate a random point through the map
	UFUNCTION(BlueprintCallable, Category="RandomWalk System")
	static FVector GetRandomReachablePoint(FVector Origin,float Radius);

	
};
