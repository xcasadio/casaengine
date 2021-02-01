#ifndef HERO_H_
#define HERO_H_

#include "Character.h"
#include "Entities\Components\AnimatedSpriteComponent.h"


class Player :
	public Character
{
public:
	Player(CasaEngine::BaseEntity* pEntity);
	virtual ~Player();

	void Initialize() override;

private:
};

#endif
