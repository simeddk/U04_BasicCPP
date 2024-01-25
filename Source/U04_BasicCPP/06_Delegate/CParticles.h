#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CParticles.generated.h"

UCLASS()
class U04_BASICCPP_API ACParticles : public AActor
{
	GENERATED_BODY()
	
public:	
	ACParticles();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void PlayParticle(int32 InValue);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

private:
	class UParticleSystem* Particles[3];
};
