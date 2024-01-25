#include "CProperty.h"
#include "../01_Print/CHelloWorld.h"


ACProperty::ACProperty()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACProperty::BeginPlay()
{
	Super::BeginPlay();

	if (!!Object)
		Object->Print();
	
}

void ACProperty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

