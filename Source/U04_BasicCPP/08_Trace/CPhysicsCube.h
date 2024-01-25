#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPhysicsCube.generated.h"

UCLASS()
class U04_BASICCPP_API ACPhysicsCube : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPhysicsCube();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
};
