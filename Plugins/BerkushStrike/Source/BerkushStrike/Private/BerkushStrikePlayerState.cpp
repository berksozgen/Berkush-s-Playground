// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "BerkushStrikePlayerState.h"

#include "Net/UnrealNetwork.h"

void ABerkushStrikePlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABerkushStrikePlayerState, PlayerIndex);
}


