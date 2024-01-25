#include "U04_BasicCPPGameModeBase.h"
#include "Global.h"
#include "Characters/CPlayer.h"

AU04_BasicCPPGameModeBase::AU04_BasicCPPGameModeBase()
{
	/*ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"));

	if (pawnAsset.Succeeded())
		DefaultPawnClass = pawnAsset.Class;*/

	CHelpers::GetClass(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
}