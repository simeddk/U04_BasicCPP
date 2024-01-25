#include "CSpotLights.h"
#include "Global.h"
#include "Components/SpotLightComponent.h"
#include "CMulticast.h"

ACSpotLights::ACSpotLights()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");

	for (int32 i = 0; i < 3; i++)
	{
		FString name;
		name.Append("SpotLight");
		name.Append(FString::FromInt(i));

		CHelpers::CreateSceneComponent(this, &SpotLights[i], FName(name), Root);

		SpotLights[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		SpotLights[i]->SetIntensity(1e+5f);
		SpotLights[i]->SetOuterConeAngle(25.f);
		SpotLights[i]->SetRelativeRotation(FRotator(-90, 0, 0));
	}
}

void ACSpotLights::BeginPlay()
{
	Super::BeginPlay();
	
	//Binding Multicast Event
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACMulticast::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACMulticast* multiTrigger = Cast<ACMulticast>(actors[0]);
	CheckNull(multiTrigger);

	multiTrigger->OnMulticastOveralp.AddUFunction(this, "RandomLight");
}

void ACSpotLights::RandomLight(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
		SpotLights[i]->SetLightColor(FLinearColor::White);

	SpotLights[InIndex]->SetLightColor(InColor);
}

