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

	UFUNCTION(BlueprintCallable, Category="CharacterInventory")
	static void AddActorInventory(AActor* targetPlayer,AActor* actor, int32 quantity);

	UFUNCTION(BlueprintCallable,Category="Health System")
	static float ReduceHealth(float damage,float health);

	UFUNCTION(BlueprintCallable,Category="Health System")
	static bool isPlayerDead(float health);

	
};
