// Fill out your copyright notice in the Description page of Project Settings.


#include "Lesta_Base_Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"

// Sets default values
ALesta_Base_Character::ALesta_Base_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 
	CameraBoom->bUsePawnControlRotation = true;

	m_tppCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("tppCamera"));
	m_tppCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ALesta_Base_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALesta_Base_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALesta_Base_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALesta_Base_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALesta_Base_Character::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("TurnRate", this, &ALesta_Base_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALesta_Base_Character::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALesta_Base_Character::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ALesta_Base_Character::StopJump);
}

void ALesta_Base_Character::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ALesta_Base_Character::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ALesta_Base_Character::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALesta_Base_Character::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALesta_Base_Character::StartJump()
{
	bPressedJump = true;
}

void ALesta_Base_Character::StopJump()
{
	bPressedJump = false;
}
