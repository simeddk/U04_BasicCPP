#include "CStaticMesh_Cone.h"

ACStaticMesh_Cone::ACStaticMesh_Cone()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/StaticMeshes/SM_Cone"));

	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);

}