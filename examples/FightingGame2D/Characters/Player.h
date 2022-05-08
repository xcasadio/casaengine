#pragma once

#include "Character.h"
#include "Entities/BaseEntity.h"

using namespace CasaEngine;

class Player :
	public Character
{
public:
	Player(BaseEntity* pEntity);
	~Player() override;

	void Initialize() override;
};
