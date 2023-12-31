// Fill out your copyright notice in the Description page of Project Settings.


#include "TPAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UTPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* MyChar = Cast<ACharacter>(TryGetPawnOwner());
	if (IsValid(MyChar))
	{
		
		Speed = MyChar->GetCharacterMovement()->Velocity.Size2D();

		ShouldMove = (Speed > 3.0f) && UKismetMathLibrary::NotEqual_VectorVector(MyChar->GetCharacterMovement()->GetCurrentAcceleration(), FVector::ZeroVector, 0);
		IsFalling = MyChar->GetCharacterMovement()->IsFalling();
	}
}
