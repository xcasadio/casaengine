#include "Base.h"
#include "Player.h"
#include "PlayerController.h"

/**
 *
 */
Player::Player(BaseEntity* pEntity) :
	Character(pEntity)
{
	m_FuryPoint = 0;
	m_FuryPointDecrease = 0.0f;
	m_InBleedingMode = false;
}

/**
 *
 */
Player::~Player()
{
}

void Player::Initialize()
{
	SetController(::new PlayerController(this, 0));
	Character::Initialize();
}

int Player::FuryPoint() const
{
	return m_FuryPoint;
}

void Player::FuryPoint(int val)
{
	m_FuryPoint = val;
	if (m_FuryPoint < 0)
	{
		m_FuryPoint = 0;
	}

	if (m_FuryPoint > m_MaxFuryPoint)
	{
		m_FuryPoint = m_MaxFuryPoint;
	}
}

float Player::FuryPointDecrease() const
{
	return m_FuryPointDecrease;
}

void Player::FuryPointDecrease(float val)
{
	m_FuryPointDecrease = val;
}

bool Player::InBleedingMode() const
{
	return m_InBleedingMode;
}

void Player::InBleedingMode(bool val)
{
	m_InBleedingMode = val;
}

int Player::FuryForce() const
{
	return m_FuryForce;
}

void Player::FuryForce(int val)
{
	m_FuryForce = val;
}

int Player::FuryDef() const
{
	return m_FuryDef;
}

void Player::FuryDef(int val)
{
	m_FuryDef = val;
}

float Player::FurySpeed() const
{
	return m_FurySpeed;
}

void Player::FurySpeed(float val)
{
	m_FurySpeed = val;
}

bool Player::FuryModeDesabling() const
{
	return m_FuryModeDesabling;
}

void Player::FuryModeDesabling(bool val)
{
	m_FuryModeDesabling = val;
}

bool Player::FuryModeEnabling() const
{
	return m_FuryModeEnabling;
}

void Player::FuryModeEnabling(bool val)
{
	m_FuryModeEnabling = val;
}

bool Player::InFuryMode() const
{
	return m_InFuryMode;
}

void Player::InFuryMode(bool val)
{
	m_InFuryMode = val;
}

int Player::MaxFuryPoint() const
{
	return m_MaxFuryPoint;
}

void Player::MaxFuryPoint(int val)
{
	m_MaxFuryPoint = val;
}