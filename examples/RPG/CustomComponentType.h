#pragma once

#include "Entities\ComponentTypeEnum.h"

using namespace CasaEngine;

enum class CustomComponentType
{
	//CHARACTER_COMPONENT = ComponentType::CUSTOM_COMPONENT + 1,
	HERO_COMPONENT = ComponentType::CUSTOM_COMPONENT + 1,
	ENEMY_COMPONENT = ComponentType::CUSTOM_COMPONENT + 2,
	ENEMY_CHIEF_COMPONENT = ComponentType::CUSTOM_COMPONENT + 3,
	BOSS_COMPONENT = ComponentType::CUSTOM_COMPONENT + 4,
};
