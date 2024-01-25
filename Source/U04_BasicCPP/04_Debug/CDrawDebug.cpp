#include "CDrawDebug.h"
#include "Global.h"

ACDrawDebug::ACDrawDebug()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = FBox(FVector(-50, -100, -50), FVector(+50, +100, +50));

	RelativeLocation[0] = FVector(0, 0, 0);
	RelativeLocation[1] = FVector(0, -500, 0);
	RelativeLocation[2] = FVector(-500, 0, 0);
	RelativeLocation[3] = FVector(-1000, 0, 0);
}

void ACDrawDebug::BeginPlay()
{
	Super::BeginPlay();

	/*DrawDebugBox
	(
		GetWorld(),
		GetActorLocation() +  Box.GetCenter(),
		Box.GetExtent(),
		FColor::Red,
		true
	);*/
}

void ACDrawDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < 4; i++)
		GlobalLocation[i] = GetActorLocation() + RelativeLocation[i];

	DrawDebugSolidBox(GetWorld(), GlobalLocation[0] + Box.GetCenter(), Box.GetExtent(), FColor::Emerald);
	DrawDebugPoint(GetWorld(), GlobalLocation[1], 50, FColor::Red);
	DrawDebugSphere(GetWorld(), GlobalLocation[2], 100, 30, FColor::Blue);
	DrawDebugCircle(GetWorld(), GlobalLocation[3], 100, 30, FColor::Green);

	FVector start = GlobalLocation[1]; //Point
	FVector end = GlobalLocation[3]; //Circle
	DrawDebugDirectionalArrow(GetWorld(), start, end, 200, FColor::Magenta);

	FVector sinLocation = GlobalLocation[2];
	sinLocation.X += sin(GetWorld()->GetTimeSeconds() * 3.f) * 200.f;
	DrawDebugSphere(GetWorld(), sinLocation, 100, 30, FColor::Red);

}

