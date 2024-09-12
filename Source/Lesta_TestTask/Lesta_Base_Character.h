// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Lesta_Base_Character.generated.h"

UCLASS()
class LESTA_TESTTASK_API ALesta_Base_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALesta_Base_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
