#pragma once

#include "Game/Game.hpp"
#include "Graphics/Effects/Program.hpp"

using namespace CasaEngine;

class CubeGame :
	public Game
{
public:
	CubeGame();

	void Initialize() override;
	void LoadContent() override;
	void Draw() override;


private:
	Program* m_pProgram;
};
