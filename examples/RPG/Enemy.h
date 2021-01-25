#ifndef ENEMY_H_
#define ENEMY_H_

#include "Character.h"
#include <map>
#include "CharacterEnum.h"
#include "Animations\Animation2D.h"
#include "Entities\Components\AnimatedSpriteComponent.h"

using namespace CasaEngine;

class Enemy :
	public Character
{
public:
	Enemy(BaseEntity* pEntity);
	virtual ~Enemy();

	void Initialize() override;

private:
};

#endif
