#include "CPhysicsCube.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"

ACPhysicsCube::ACPhysicsCube()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	UStaticMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Cube.SM_Cube'");
	Mesh->SetStaticMesh(meshAsset);
	Mesh->SetRelativeScale3D(FVector(0.7f));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

}

void ACPhysicsCube::BeginPlay()
{
	Super::BeginPlay();
	
}

