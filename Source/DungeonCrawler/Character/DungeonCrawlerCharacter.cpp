#include "DungeonCrawlerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SpotLightComponent.h"
#include "DungeonCrawler/Character/AI_Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

ADungeonCrawlerCharacter::ADungeonCrawlerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	//Define var HealthSystem
	this->health = 100.f;

	//Define var DamageSystem
	this->damage = 10.f;

	//Define FlashLight var
	this->intensity = 3300.f;
	this->outerConeAngle = 26.f;
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 150.0f; // The camera follows at this distance behind the character
	CameraBoom->SetRelativeLocation(FVector(0.0f,0.0f,70.0f));
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Create a FlashLight
	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
	
	FlashLight->OuterConeAngle = outerConeAngle;
	FlashLight->Intensity = this->intensity;
	
	FlashLight->AddLocalRotation(FRotator(90.0f,0.0f,0.0f));
	FlashLight->AttachToComponent(this->FindComponentByClass<USceneComponent>(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_r"));
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADungeonCrawlerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("FlashLight", IE_Pressed,this, &ADungeonCrawlerCharacter::TurnFlashLight);
	PlayerInputComponent->BindAction("OpenDoor", IE_Pressed,this, &ADungeonCrawlerCharacter::LineTraceForObjects);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ADungeonCrawlerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ADungeonCrawlerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ADungeonCrawlerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ADungeonCrawlerCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADungeonCrawlerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADungeonCrawlerCharacter::TouchStopped);
}

void ADungeonCrawlerCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ADungeonCrawlerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADungeonCrawlerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ADungeonCrawlerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ADungeonCrawlerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ADungeonCrawlerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ADungeonCrawlerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADungeonCrawlerCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

//Turn on / off the flash light
void ADungeonCrawlerCharacter::TurnFlashLight()
{
	this->FlashLight->ToggleVisibility();
}

//Make a line trace for objects -> open door -> attack -> add inventory...
void ADungeonCrawlerCharacter::LineTraceForObjects()
{
	FHitResult OutHit;
	FCollisionQueryParams CollisionQueryParams;

	float delay = 5.0f;
	
	FVector Start;
	FRotator CameraRotator;
	
	GetController()->GetPlayerViewPoint(Start,CameraRotator);
	FVector End = Start + (CameraRotator.Vector() * 1000.0f);

	bool bHitObject = GetWorld()->LineTraceSingleByChannel(OutHit,Start,End,ECC_Visibility,CollisionQueryParams);

	DrawDebugLine(GetWorld(),Start,End,FColor::Red,false,2.0f);

	//Get Actors
	ADoor* door = Cast<ADoor>(OutHit.GetActor());
	AKeyActor* keyactor = Cast<AKeyActor>(OutHit.GetActor());
	AAI_Enemy* enemy = Cast<AAI_Enemy>(OutHit.GetActor());
	
	if(bHitObject && door != nullptr && this->characterInventory.Contains(keyInventory) && (!door->isOpen))
	{
		door->TranslateDoor();
	}
	
	if(bHitObject && keyactor != nullptr)
	{
		UBFL_Main::AddActorInventory(this,keyactor,1);
		this->keyInventory = keyactor;
	}
	if(bHitObject && enemy !=nullptr)
	{
		//Debug for me 
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy"));
		OutHit.GetActor()->TakeDamage(this->damage,FDamageEvent(UDamageType::StaticClass()),
			GetWorld()->GetFirstPlayerController(),this);
	}
}

float ADungeonCrawlerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	this->health = UBFL_Main::ReduceHealth(DamageAmount,this->health);
	UBFL_Main::isPlayerDead(this->health) ? this->isDead = true, true : false;
	
	return DamageAmount;
}







