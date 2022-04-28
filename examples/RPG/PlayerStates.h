#pragma once

#include "GameTime.h"
#include "AI\FSM\IState.h"
#include "GameDatas/IController.h"

using namespace CasaEngine;

typedef enum PlayerControllerState
{
	GLOBAL,
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


class PlayerStateGlobal :
	public IState<IController>
{
public:
	PlayerStateGlobal();
	~PlayerStateGlobal() override;

	void Enter(IController* pController_) override;
	void Execute(IController* pController_, const GameTime& elpasedTime) override;
	void Exit(IController* pController_) override;
	bool OnMessage(IController* pController_, const Telegram& msg) override;

private:
};


class PlayerStateIdle :
	public IState<IController>
{
public:
	PlayerStateIdle();
	~PlayerStateIdle() override;

	void Enter(IController* pController_) override;
	void Execute(IController* pController_, const GameTime& elpasedTime_) override;
	void Exit(IController* pController_) override;
	bool OnMessage(IController* pController_, const Telegram& msg) override;

private:
};


class PlayerStateWalking :
	public IState<IController>
{
public:
	PlayerStateWalking();
	~PlayerStateWalking() override;

	void Enter(IController* pController_) override;
	void Execute(IController* pController_, const GameTime& elpasedTime_) override;
	void Exit(IController* pController_) override;
	bool OnMessage(IController* pController_, const Telegram& msg) override;

private:
};


class PlayerStateAttack :
	public IState<IController>
{
public:
	PlayerStateAttack();
	~PlayerStateAttack() override;

	void Enter(IController* pController_) override;
	void Execute(IController* pController_, const GameTime& elpasedTime_) override;
	void Exit(IController* pController_) override;
	bool OnMessage(IController* pController_, const Telegram& msg) override;

private:
};
