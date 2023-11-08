#pragma once

#include  "Character.hpp"
#include  "Entities/Components/AnimatedSpriteComponent.hpp"

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
