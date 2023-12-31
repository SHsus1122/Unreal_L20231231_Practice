// Fill out your copyright notice in the Description page of Project Settings.


#include "TPCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATPCharacter::ATPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringAmr"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
}

// Called when the game starts or when spawned
void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UEIC)
	{
		UEIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ATPCharacter::Jump);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ATPCharacter::Jump);

		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATPCharacter::Move);
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ATPCharacter::Look);
	}
}

void ATPCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Dir = Value.Get<FVector2D>();

	FRotator CameraRotation = GetControlRotation();
	FRotator DirectionRot = FRotator(0, CameraRotation.Yaw, 0);

	FVector ForWardVector = UKismetMathLibrary::GetForwardVector(DirectionRot);
	FVector RightVector = UKismetMathLibrary::GetRightVector(DirectionRot);

	AddMovementInput(ForWardVector, Dir.Y);
	AddMovementInput(RightVector, Dir.X);
}

void ATPCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Dir = Value.Get<FVector2D>();

	AddControllerYawInput(Dir.X);
	AddControllerPitchInput(Dir.Y);
}

