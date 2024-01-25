#include "CDropBox.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CMulticast.h"

ACDropBox::ACDropBox()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");

	UStaticMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Cube.SM_Cube'");

	for (int32 i = 0; i < 3; i++)
	{
		FString name;
		name.Append("Mesh");
		name.Append(FString::FromInt(i));

		CHelpers::CreateSceneComponent(this, &Boxes[i], FName(name), Root);

		Boxes[i]->SetStaticMesh(meshAsset);
		Boxes[i]->SetRelativeLocation(FVector(0, i * 150, 0));
	}
}

void ACDropBox::BeginPlay()
{
	Super::BeginPlay();
	
	//Get Material Instance
	UMaterialInstanceConstant* materialAsset;
	CHelpers::GetAssetDynamic(&materialAsset, "/Game/Materials/MAT_StaticMesh_Inst");

	for (int32 i = 0; i < 3; i++)
	{
		//Create Dynamic Material
		DynamicMaterials[i] = UMaterialInstanceDynamic::Create(materialAsset, this);
		Boxes[i]->SetMaterial(0, DynamicMaterials[i]);

		//Save OriginLocation
		OriginLocation[i] = Boxes[i]->GetComponentToWorld().GetLocation();
	}

	//Binding Multicast Event
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACMulticast::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACMulticast* multiTrigger = Cast<ACMulticast>(actors[0]);
	CheckNull(multiTrigger);

	multiTrigger->OnMulticastOveralp.AddUFunction(this, "RandomDrop");

	multiTrigger->OnMulticastOveralp.AddLambda([&](int32 InIndex, FLinearColor InColor) 
		{ 
			Index = InIndex;

			FString str;
			str.Append("Index : ");
			str.Append(FString::FromInt(Index));
			str.Append(", Color : ");
			str.Append(InColor.ToString());

			CLog::Log(str);
		});
	
}

void ACDropBox::RandomDrop(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		Boxes[i]->SetWorldLocation(OriginLocation[i]);
		Boxes[i]->SetSimulatePhysics(false);
		DynamicMaterials[i]->SetVectorParameterValue("BaseColor", FLinearColor::White);
	}

	Boxes[InIndex]->SetSimulatePhysics(true);
	DynamicMaterials[InIndex]->SetVectorParameterValue("BaseColor", InColor);
}

