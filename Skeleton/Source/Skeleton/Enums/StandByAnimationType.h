#pragma once

#include "StandByAnimationType.generated.h"

UENUM(BlueprintType)
enum class EStandByAnimationType : uint8
{
	NONE = 0,

	STANDBY_0 = 1,
	STANDBY_1 = 2,
	STANDBY_2 = 3,
	STANDBY_3 = 4,
	STANDBY_4 = 5,
	STANDBY_5 = 6,
};