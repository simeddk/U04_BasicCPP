#include "CSpawner.h"
#include "CStaticMesh.h"

ACSpawner::ACSpawner()
{

}

void ACSpawner::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Error, TEXT("%s"), *ClassRef->GetName());

	for (int32 i = 0; i < 4; i++)
	{
		FTransform transform; //Scale, Rotation, Location
		Spawned[i] = GetWorld()->SpawnActor<ACStaticMesh>(SpawnClasses[i], transform);

		FVector location = GetActorLocation();
		Spawned[i]->SetActorLocation(FVector(location.X, location.Y + i * 200, location.Z));
	}
}
