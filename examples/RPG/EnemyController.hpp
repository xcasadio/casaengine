#pragma once

#include  "GameDatas/IController.hpp"
#include  "GameTime.hpp"
#include  "AI/FSM/StateMachine.hpp"
#include  "AI/FSM/IState.hpp"
#include <map>

#include  "Character.hpp"
#include  "CharacterEnum.hpp"
#include  "Maths/Vector2.hpp"

using namespace CasaEngine;

class EnemyController :
	public IController
{
public:
	EnemyController(Character* pCharacter);
	~EnemyController();

	void Initialize() override;
	void Update(const GameTime& elapsedTime_) override;
};
