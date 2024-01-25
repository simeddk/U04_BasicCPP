#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawner.generated.h"

UCLASS()
class U04_BASICCPP_API ACSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpawner();

protected:
	virtual void BeginPlay() override;

private:
	//All Class Ref Showing
	UPROPERTY(EditDefaultsOnly)
		UClass* ClassRef;

	//Specific Sub Class Showing
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACStaticMesh> SubClassOf;

	//Array
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACStaticMesh> SpawnClasses[4];

private:
	class ACStaticMesh* Spawned[4];
};
