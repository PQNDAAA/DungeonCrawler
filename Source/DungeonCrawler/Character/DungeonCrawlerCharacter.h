#pragma once

#include "CoreMinimal.h"
#include "DungeonCrawler/Actors/KeyActor.h"
#include "DungeonCrawler/Library/BFL_Main.h"
#include "DungeonCrawler/Actors/Door.h"
#include "GameFramework/Character.h"
#include "DungeonCrawlerCharacter.generated.h"

UCLASS(config=Game)
class ADungeonCrawlerCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ADungeonCrawlerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FlashLight, meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* FlashLight;

	/**Based on the health system, storage the health*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Stats)
	float health;

	/**FlashLight intensity*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=FlashLight)
	float intensity;

	/**FlashLight cone angle*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=FlashLight)
	float outerConeAngle;

	/**Check if the player is dead */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=boolState)
	bool isDead;

	/**Player Inventory*/
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Inventory)
	TMap<AActor*, int32> characterInventory;

	AKeyActor* keyInventory;

protected:
	
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called to turn on/off the flash light*/
	void TurnFlashLight();
	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called at the beginning
	virtual void BeginPlay() override;
	
public:
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, Category="HealthSystem")
	float GetHealth() const { return health; }
	
	UFUNCTION(BlueprintCallable, Category="HealthSystem")
	float ReduceHealth(float value) { return health -= value;}
	
	UFUNCTION(BlueprintCallable, Category="HealthSystem")
	float AddHealth(float value) { return health += value;}

	UFUNCTION(BlueprintCallable, Category="HealthSystem")
	void PlayerIsDead();

	UFUNCTION(BlueprintCallable, Category="LineTraceObjects")
	void LineTraceForObjects();

private:

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser) override;
	
};

