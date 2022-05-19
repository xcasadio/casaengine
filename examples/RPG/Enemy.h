#pragma once

#include "Character.h"
#include "Entities\Components\AnimatedSpriteComponent.h"

using namespace CasaEngine;

class Enemy :
	public Character
{
public:
	Enemy(BaseEntity* pEntity);
	~Enemy() override;

	void Initialize() override;

private:
};
