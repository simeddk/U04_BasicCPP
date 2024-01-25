#include "CStaticMesh_Cylinder.h"

ACStaticMesh_Cylinder::ACStaticMesh_Cylinder()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/StaticMeshes/SM_Cylinder"));

	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);
}