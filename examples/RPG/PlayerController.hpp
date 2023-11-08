#pragma once

#include  "GameDatas/IController.hpp"
#include  "GameTime.hpp"
#include  "CharacterEnum.hpp"
#include  "Maths/Vector2.hpp"
#include  "Player.hpp"

using namespace CasaEngine;

typedef unsigned int PlayerIndex;

class PlayerController :
	public IController
{
public:
	PlayerController(Player* pHero, PlayerIndex index_);
	~PlayerController() override;

	void Initialize() override;
	void Update(const GameTime& elapsedTime) override;

	Player* GetPlayer() const;

	bool IsAttackButtonJustPressed();
	bool IsAttackButtonPressed();

	Orientation GetDirectionFromInput(Vector2& direction_);

private:
	PlayerIndex m_PlayerIndex;
	Player* m_pHero;
};
