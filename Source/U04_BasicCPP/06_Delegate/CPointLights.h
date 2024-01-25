#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPointLights.generated.h"

UCLASS()
class U04_BASICCPP_API ACPointLights : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPointLights();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnLight();

	UFUNCTION()
		void OffLight();

	UFUNCTION()
		FString OnRandomColor(FLinearColor InColor);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* Light1;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* Light2;
};
