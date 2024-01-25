#include "CStaticMesh.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACStaticMesh::ACStaticMesh()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/StaticMeshes/SM_Cube.SM_Cube'"));
	
	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);

	
}

void ACStaticMesh::BeginPlay()
{
	Super::BeginPlay();
	
	//Get Material Asset
	UObject* asset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Materials/MAT_StaticMesh_Inst.MAT_StaticMesh_Inst'"));
	UMaterialInstanceConstant* materialAsset =Cast<UMaterialInstanceConstant>(asset);

	//Create Dynamic Material
	DynamicMaterial = UMaterialInstanceDynamic::Create(materialAsset, this);
	Mesh->SetMaterial(0, DynamicMaterial);

	//Set Timer
	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.f, true);
}

void ACStaticMesh::ChangeColor()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.f;

	DynamicMaterial->SetVectorParameterValue("BaseColor", color);
	DynamicMaterial->SetScalarParameterValue("Metalic", color.R);
	DynamicMaterial->SetScalarParameterValue("Roughness", color.R);
		
}

