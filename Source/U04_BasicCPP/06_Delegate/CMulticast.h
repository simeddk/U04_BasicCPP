#pragma once

#include "CoreMinimal.h"
#include "05_Collision/CBoxBase.h"
#include "CMulticast.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastOveralpSignature, int32, FLinearColor);

UCLASS()
class U04_BASICCPP_API ACMulticast : public ACBoxBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FMulticastOveralpSignature OnMulticastOveralp;
};
