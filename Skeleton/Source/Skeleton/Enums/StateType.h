#pragma once

#include "StateType.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	NONE = 0,

	IDLE = 1,
	MOVE = 2,
	FALLING = 4,
	STANDBY = 5,

	DODGE = 6,
	JUMP = 7,

	ATTACK = 8,

	LANDING = 9,

	DEAD = 10,
};