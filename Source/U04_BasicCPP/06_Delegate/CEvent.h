#pragma once

#include "CoreMinimal.h"
#include "05_Collision/CBoxBase.h"
#include "CEvent.generated.h"

UCLASS()
class U04_BASICCPP_API ACEvent : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	DECLARE_EVENT_OneParam(ACEvent, FEventOverlapSignatrue, int32);

	FEventOverlapSignatrue OnEventOverlap;
};
