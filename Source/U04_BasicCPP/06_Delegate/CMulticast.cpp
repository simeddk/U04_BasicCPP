#include "CMulticast.h"
#include "Global.h"

void ACMulticast::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACMulticast::ActorBeginOverlap);
}

void ACMulticast::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnMulticastOveralp.IsBound())
	{
		int32 randomIndex = UKismetMathLibrary::RandomIntegerInRange(0, 2);
		FLinearColor randomColor = FLinearColor::MakeRandomColor();

		OnMulticastOveralp.Broadcast(randomIndex, randomColor);
	}
}
