#ifndef EnemyController_H_
#define EnemyController_H_

#include "GameDatas/IController.h"
#include "GameTime.h"
#include "AI\FSM\StateMachine.h"
#include "AI\FSM\IState.h"
#include <map>

#include "Character.h"
#include "CharacterEnum.h"
#include "Maths\Vector2.h"

using namespace CasaEngine;

class EnemyController :
	public IController
{
public:
	EnemyController(Character* pCharacter);
	~EnemyController();

	void Initialize() override;
	void Update(const GameTime elapsedTime_) override;
};

#endif
