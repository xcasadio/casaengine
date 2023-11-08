#pragma once

#include "Game/Game.hpp"
#include "World/World.hpp"

using namespace CasaEngine;

class TileMapGame :
	public Game
{
public:
	TileMapGame();
	~TileMapGame() override;

	void Initialize() override;
	void LoadContent() override;
	void Draw() override;
	void Update(const GameTime& gameTime_) override;
};
