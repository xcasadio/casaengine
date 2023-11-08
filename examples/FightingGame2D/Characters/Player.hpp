#pragma once

#include  "Character.hpp"
#include  "Entities/BaseEntity.hpp"

using namespace CasaEngine;

class Player :
	public Character
{
public:
	Player(BaseEntity* pEntity);
	~Player() override;

	void Initialize() override;
};
