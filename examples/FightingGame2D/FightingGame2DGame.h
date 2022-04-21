#pragma once

#include "GameTime.h"
#include "Game/Game.h"

#include "Sprite/SpriteRenderer.h"
#include "World/World.h"
#include "Entities/Components/AnimatedSpriteComponent.h"

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
	std::vector<Animation2DData> LoadAnimations();
	void LoadSprites();
	void DisplayUI();

private:
	World* m_pWorld;
};
