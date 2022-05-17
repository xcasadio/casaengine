#pragma once

#include "GameTime.h"
#include "Game/Game.h"

#include "World/World.h"

using namespace CasaEngine;

class FightingGame2DGame :
	public Game
{
public:

	FightingGame2DGame();
	~FightingGame2DGame() override;

	void Initialize() override;
	void LoadContent() override;
	void Update(const GameTime& gameTime_) override;
	void Draw() override;

private:
	void DisplayUI();

	World* m_pWorld;
};
