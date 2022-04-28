#pragma once
#include "Character.h"
#include "Entities\Components\AnimatedSpriteComponent.h"


class Player :
	public Character
{
public:
	Player(CasaEngine::BaseEntity* pEntity);
	~Player() override;

	void Initialize() override;

private:
};
