#include "CComponentOverlap.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"

ACComponentOverlap::ACComponentOverlap()
{
	CHelpers::CreateSceneComponent(this, &Light, "Light", Root);

	Light->SetLightColor(FLinearColor::Red);
}

void ACComponentOverlap::BeginPlay()
{
	Super::BeginPlay();

	Light->SetVisibility(false);

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACComponentOverlap::ComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACComponentOverlap::ComponentEndOverlap);
}

void ACComponentOverlap::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Light->SetVisibility(true);
}

void ACComponentOverlap::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Light->SetVisibility(false);
}
