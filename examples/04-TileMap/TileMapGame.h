#pragma once

#include "Game/Game.h"
#include "World/World.h"

using namespace CasaEngine;

class TileMapGame :
	public Game
{
public:
	TileMapGame();
	~TileMapGame() override;

	void Initialize() override;
	void CreateBackground(World* pWorld);
	void LoadContent() override;
	void Draw() override;
	void Update(const GameTime& gameTime_) override;
};
