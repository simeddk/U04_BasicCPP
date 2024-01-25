#include "CSphereTrigger.h"
#include "Global.h"
#include "CSphereTrace.h"

void ACSphereTrigger::BeginPlay()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACSphereTrace::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACSphereTrace* trace = Cast<ACSphereTrace>(actors[0]);
	CheckNull(trace);

	OnActorBeginOverlap.AddDynamic(trace, &ACSphereTrace::DoSphereTrace);
}