#include "CHelloWorld.h"

ACHelloWorld::ACHelloWorld()
{
	PrimaryActorTick.bCanEverTick = true;

	//Called just build
	GLog->Log("Hell World");

	UE_LOG(LogTemp, Error, L"Hell World");

	//AActor* actor = nullptr;
	//actor->SetActorLocation(FVector(100, 100, 100));
}

void ACHelloWorld::BeginPlay()
{
	Super::BeginPlay();

	
}

void ACHelloWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACHelloWorld::Print()
{
	UE_LOG(LogTemp, Warning, L"Print is Called");
}

