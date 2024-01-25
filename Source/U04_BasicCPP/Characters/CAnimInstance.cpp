#include "CAnimInstance.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Characters/IRifle.h"
#include "Characters/CRifle.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Player = Cast<ACPlayer>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(Player);
	Speed = Player->GetVelocity().Size2D();

	FRotator controlRotation = FRotator(0, Player->GetControlRotation().Yaw, 0);
	Direction = CalculateDirection(Player->GetVelocity(), controlRotation);

	Pitch = Player->GetBaseAimRotation().Pitch;

	IIRifle* rifleCharacter = Cast<IIRifle>(Player);
	if (!!rifleCharacter)
	{
		bEquipped = rifleCharacter->GetRifle()->IsEquipped();
		bAiming = rifleCharacter->GetRifle()->IsAiming();
	}
}