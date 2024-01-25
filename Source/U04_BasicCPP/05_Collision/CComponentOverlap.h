#pragma once

#include "CoreMinimal.h"
#include "05_Collision/CBoxBase.h"
#include "CComponentOverlap.generated.h"

UCLASS()
class U04_BASICCPP_API ACComponentOverlap : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACComponentOverlap();

protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
		void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex,	bool bFromSweep,	const FHitResult& SweepResult);

	UFUNCTION()
		void ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* Light;
};
