// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler/Character/DungeonCrawlerCharacter.h"
#include "BFL_Main.h"

void UBFL_Main::AddActorInventory(AActor* targetPlayer,AActor* actor, int32 quantity)
{
	ADungeonCrawlerCharacter* player = Cast<ADungeonCrawlerCharacter>(targetPlayer);

	//Add
	player->characterInventory.Add(actor,quantity);
	
	//Debug 
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Item added and destroy.")));
	actor->K2_DestroyActor();

}

float UBFL_Main::ReduceHealth(float damage, float health)
{
	return health -= damage;
}

bool UBFL_Main::isPlayerDead(float health)
{
	return health <= 0.f;
}

FVector UBFL_Main::GetRandomReachablePoint(FVector Origin,float Radius)
{
		FVector2d randomPoint = FMath::RandPointInCircle(Radius);
		FVector Point = Origin + FVector(randomPoint.X,randomPoint.Y,Origin.Z);

		return Point;
}








