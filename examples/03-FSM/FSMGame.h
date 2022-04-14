#pragma once

#include "Game/Game.h"

using namespace CasaEngine;


class FSMGame :
	public Game
{
public:
	FSMGame();
	~FSMGame() override;

	void Initialize() override;

private:
	BaseEntity* m_pBob, * m_pElsa;
};
