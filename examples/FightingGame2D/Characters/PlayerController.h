#ifndef PLAYERCONTROLLER_H_
#define PLAYERCONTROLLER_H_

#include "GameDatas/IController.h"
#include "GameTime.h"
#include "Maths\Vector2.h"
#include "Player.h"

using namespace CasaEngine;

typedef unsigned int PlayerIndex;

class PlayerController :
	public IController
{
public:
	PlayerController(Player* pHero, PlayerIndex index_);
	~PlayerController();

	void Initialize() override;
	void Update(const GameTime elapsedTime_) override;

	Player* GetPlayer() const;

	bool IsAttackButtonJustPressed();
	bool IsAttackButtonPressed();

	orientation GetDirectionFromInput(Vector2& direction_);

private:
	PlayerIndex m_PlayerIndex;
	Player* m_pPlayer;
};

#endif
