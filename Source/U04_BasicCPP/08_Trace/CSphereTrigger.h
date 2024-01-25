#pragma once

#include "CoreMinimal.h"
#include "05_Collision/CBoxBase.h"
#include "CSphereTrigger.generated.h"

UCLASS()
class U04_BASICCPP_API ACSphereTrigger : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
