#include "CPointLights.h"
#include "Global.h"
#include "Components/PointLightComponent.h"
#include "CDelegate.h"

ACPointLights::ACPointLights()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Light1, "Light1", Root);
	CHelpers::CreateSceneComponent(this, &Light2, "Light2", Root);

	Light1->SetIntensity(1e+4f);
	Light1->SetAttenuationRadius(200.f);
	Light1->SetLightColor(FLinearColor::Red);

	Light2->SetRelativeLocation(FVector(0, 200, 0));
	Light2->SetIntensity(1e+4f);
	Light2->SetAttenuationRadius(200.f);
	Light2->SetLightColor(FLinearColor::Green);
}

void ACPointLights::BeginPlay()
{
	Super::BeginPlay();
	
	Light1->SetVisibility(false);
	Light2->SetVisibility(false);

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACDelegate::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACDelegate* trigger = Cast<ACDelegate>(actors[0]);
	CheckNull(trigger);

	trigger->OnDelegateBegin.BindUFunction(this, "OnLight");
	trigger->OnDelegateEnd.BindUFunction(this, "OffLight");
	trigger->OnRetValOneParam.BindUFunction(this, "OnRandomColor");
}

void ACPointLights::OnLight()
{
	Light1->SetVisibility(true);
	
}

void ACPointLights::OffLight()
{
	Light1->SetVisibility(false);
	Light2->SetVisibility(false);
}

FString ACPointLights::OnRandomColor(FLinearColor InColor)
{
	Light2->SetLightColor(InColor);
	Light2->SetVisibility(true);

	return InColor.ToString();
}

