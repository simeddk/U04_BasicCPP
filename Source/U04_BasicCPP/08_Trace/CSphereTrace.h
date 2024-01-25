#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSphereTrace.generated.h"

UCLASS()
class U04_BASICCPP_API ACSphereTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSphereTrace();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void DoSphereTrace(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

};
