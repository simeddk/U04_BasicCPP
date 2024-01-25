#include "CActorOverlap.h"
#include "Global.h"

void ACActorOverlap::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACActorOverlap::ActorBeginOverlap);
}

void ACActorOverlap::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CLog::Print(OtherActor->GetName() + " is Overlapped");
}
