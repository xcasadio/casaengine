#ifndef HELLOWORLDGAME_H_
#define HELLOWORLDGAME_H_

#include "Game/Game.h"
#include "Graphics/Effects/Program.h"

using namespace CasaEngine;

/**
 *
 */
class CubeGame :
	public Game
{
public:
	CubeGame();
	~CubeGame();

	virtual void Initialize();
	virtual void LoadContent();
	virtual void Draw();
	virtual void Update(const GameTime& gameTime_);

private:
	Program* m_pProgram;
};

#endif // HELLOWORLDGAME_H_
