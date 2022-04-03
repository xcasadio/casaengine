#ifndef CUBEGAME_H_
#define CUBEGAME_H_

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

private:
	Program* m_pProgram;
};

#endif