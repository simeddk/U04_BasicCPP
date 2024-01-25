#include "CBoxBase.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACBoxBase::ACBoxBase()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Box, "Box", Root);
	CHelpers::CreateSceneComponent(this, &Text, "Text", Root);

	Box->SetHiddenInGame(false);
	Box->SetRelativeScale3D(FVector(3));

	Text->SetText(GetName());
	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetTextRenderColor(FColor::Black);
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
}

void ACBoxBase::BeginPlay()
{
	Super::BeginPlay();
	
}

