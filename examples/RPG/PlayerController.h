#ifndef PLAYERCONTROLLER_H_
#define PLAYERCONTROLLER_H_

#include "GameDatas/IController.h"
#include "GameTime.h"
#include "CharacterEnum.h"
#include "Maths\Vector2.h"
#include "Hero.h"

using namespace CasaEngine;

typedef unsigned int PlayerIndex;

class PlayerController :
	public IController
{
public:
	PlayerController(Hero* pHero, PlayerIndex index_);
	~PlayerController();

	void Initialize() override;
	void Update(const GameTime elapsedTime_) override;

	Hero* GetHero() const;

	bool IsAttackButtonJustPressed();
	bool IsAttackButtonPressed();

	orientation GetDirectionFromInput(Vector2F& direction_);

private:
	PlayerIndex m_PlayerIndex;
	Hero* m_pHero;
};

#endif
