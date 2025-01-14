#pragma once

#include "SwordAnimationType.generated.h"

UENUM(BlueprintType)
enum class ESwordAnimationType : uint8
{
	NONE = 0,

	SWORD_WEAK_ATTACK_0 = 1,
	SWORD_WEAK_ATTACK_1 = 2,
	SWORD_WEAK_ATTACK_2 = 3,

	SWORD_STRONG_ATTACK_0 = 4,
};