#ifndef FSMGAME_H_
#define FSMGAME_H_

#include "GameTime.h"
#include "Game/Game.h"
#include "Maths/Matrix4.h"
#include "Entities/BaseEntity.h"
#include "Entities/Components/Camera3DComponent.h"

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

#endif // FSMGAME_H_
