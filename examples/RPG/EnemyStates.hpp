#pragma once

#include  "GameTime.hpp"
#include  "AI/FSM/IState.hpp"
#include  "GameDatas/IController.hpp"
#include  "Character.hpp"

using namespace CasaEngine;

enum class EnemyControllerState
{
	IDLE = 0,
	MOVING = 1,
	ATTACK_1 = 2,
	ATTACK_2 = 3,
	ATTACK_3 = 4,
	MAGIC_1 = 5,
	MAGIC_2 = 6,
	HIT = 7,
	DEAD = 8,
};

class EnemyStateIdle :
	public IState<IController>
{
public:
	EnemyStateIdle();
	~EnemyStateIdle();

	void Enter(IController* pController_) override;
	void Execute(IController* pController_, const GameTime& elpasedTime_);
	void Exit(IController* pController_) override;
	bool OnMessage(IController* pController_, const Telegram& msg) override;
};

class EnemyStateWalking :
	public IState<IController>
{
public:
	EnemyStateWalking();
	~EnemyStateWalking();

	void Enter(IController* pController_) override;
	void Execute(IController* pController_, const GameTime& elpasedTime_);
	void Exit(IController* pController_) override;
	bool OnMessage(IController* pController_, const Telegram& msg) override;
};