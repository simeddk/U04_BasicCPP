#include "CEvent.h"
#include "Global.h"

void ACEvent::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACEvent::ActorBeginOverlap);
}


void ACEvent::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnEventOverlap.IsBound())
	{
		int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);

		OnEventOverlap.Broadcast(index);
	}
}
