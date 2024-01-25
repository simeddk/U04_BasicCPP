#pragma once

#include "CoreMinimal.h"
#include "05_Collision/CBoxBase.h"
#include "CActorOverlap.generated.h"

UCLASS()
class U04_BASICCPP_API ACActorOverlap : public ACBoxBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
