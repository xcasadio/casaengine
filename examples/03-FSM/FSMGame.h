#ifndef FSMGAME_H_
#define FSMGAME_H_

#include "Game/Game.h"

using namespace CasaEngine;

/**
 *
 */
class FSMGame :
	public Game
{
public:
	FSMGame();
	~FSMGame();

	void Initialize() override;

private:
	BaseEntity* m_pBob, * m_pElsa;
};

#endif
