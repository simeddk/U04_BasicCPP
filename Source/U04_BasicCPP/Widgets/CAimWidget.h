#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CAimWidget.generated.h"

UCLASS()
class U04_BASICCPP_API UCAimWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//Target Image Red
	UFUNCTION(BlueprintImplementableEvent)
		void OnTarget();

	//Target Image Whie
	UFUNCTION(BlueprintImplementableEvent)
		void OffTarget();
	
};
