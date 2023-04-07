// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawlerCharacter.h"
#include "BFL_Main.h"

void UBFL_Main::AddActorInventory(AActor* targetPlayer,AActor* actor, int32 quantity)
{
	ADungeonCrawlerCharacter* player = Cast<ADungeonCrawlerCharacter>(targetPlayer);

	player->characterInventory.Add(actor,quantity);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Item added and destroy.")));
	actor->K2_DestroyActor();

}



