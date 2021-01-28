#include "Base.h"
#include "Hero.h"
#include "PlayerController.h"

/**
 *
 */
Hero::Hero(BaseEntity* pEntity) :
	Character(pEntity)
{
	m_FuryPoint = 0;
	m_FuryPointDecrease = 0.0f;
	m_InBleedingMode = false;
}

/**
 *
 */
Hero::~Hero()
{
}

void Hero::Initialize()
{
	m_pController = ::new PlayerController(this, 0);
	Character::Initialize();
}

int Hero::FuryPoint() const
{
	return m_FuryPoint;
}

void Hero::FuryPoint(int val)
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

float Hero::FuryPointDecrease() const
{
	return m_FuryPointDecrease;
}

void Hero::FuryPointDecrease(float val)
{
	m_FuryPointDecrease = val;
}

bool Hero::InBleedingMode() const
{
	return m_InBleedingMode;
}

void Hero::InBleedingMode(bool val)
{
	m_InBleedingMode = val;
}

int Hero::FuryForce() const
{
	return m_FuryForce;
}

void Hero::FuryForce(int val)
{
	m_FuryForce = val;
}

int Hero::FuryDef() const
{
	return m_FuryDef;
}

void Hero::FuryDef(int val)
{
	m_FuryDef = val;
}

float Hero::FurySpeed() const
{
	return m_FurySpeed;
}

void Hero::FurySpeed(float val)
{
	m_FurySpeed = val;
}

bool Hero::FuryModeDesabling() const
{
	return m_FuryModeDesabling;
}

void Hero::FuryModeDesabling(bool val)
{
	m_FuryModeDesabling = val;
}

bool Hero::FuryModeEnabling() const
{
	return m_FuryModeEnabling;
}

void Hero::FuryModeEnabling(bool val)
{
	m_FuryModeEnabling = val;
}

bool Hero::InFuryMode() const
{
	return m_InFuryMode;
}

void Hero::InFuryMode(bool val)
{
	m_InFuryMode = val;
}

int Hero::MaxFuryPoint() const
{
	return m_MaxFuryPoint;
}

void Hero::MaxFuryPoint(int val)
{
	m_MaxFuryPoint = val;
}