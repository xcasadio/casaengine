#pragma once

#include  "GameTime.hpp"
#include  "AI/FSM/IState.hpp"
#include  "GameDatas/IController.hpp"

using namespace CasaEngine;

typedef enum PlayerControllerState
{
	IDLE,
	MOVING,
	ATTACK_1,
	ATTACK_2,
	ATTACK_3,
	MAGIC_1,
	MAGIC_2,
	HIT,
	DEAD,
	TO_FURY_MODE,
	TO_NORMAL_MODE,
} PlayerControllerState;

//////////////////////////////////////////

class PlayerStateIdle :
	public IState<IController>
{
public:
	PlayerStateIdle();
	~PlayerStateIdle() override;

	void Enter(IController* controller) override;
	void Execute(IController* controller, const GameTime& elpasedTime_) override;
	void Exit(IController* controller) override;
	bool OnMessage(IController* controller, const Telegram& msg) override;
};

//////////////////////////////////////////

class PlayerStateWalking :
	public IState<IController>
{
public:
	PlayerStateWalking();
	~PlayerStateWalking() override;

	void Enter(IController* controller) override;
	void Execute(IController* controller, const GameTime& elpasedTime_) override;
	void Exit(IController* controller) override;
	bool OnMessage(IController* controller, const Telegram& msg) override;
};
