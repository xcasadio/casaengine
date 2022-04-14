#pragma once

#include "Game/Game.h"
#include "Graphics/Effects/Program.h"

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
