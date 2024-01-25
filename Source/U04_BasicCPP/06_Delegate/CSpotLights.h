#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpotLights.generated.h"

UCLASS()
class U04_BASICCPP_API ACSpotLights : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpotLights();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void RandomLight(int32 InIndex, FLinearColor InColor);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class USpotLightComponent* SpotLights[3];

};
