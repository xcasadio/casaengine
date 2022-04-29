#include "Base.h"
#include "Player.h"
#include "PlayerController.h"


Player::Player(BaseEntity* pEntity) :
	Character(pEntity),
	m_FuryPoint(0),
	m_FuryPointDecrease(0.0f),
	m_InBleedingMode(false),
	m_FuryForce(0),
	m_FuryDef(0),
	m_FurySpeed(0),
	m_FuryModeEnabling(false),
	m_FuryModeDisabling(false),
	m_InFuryMode(false),
	m_MaxFuryPoint(0),
	m_Weapon(nullptr)
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

bool Player::FuryModeDisabling() const
{
	return m_FuryModeDisabling;
}

void Player::FuryModeDisabling(bool val)
{
	m_FuryModeDisabling = val;
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

void Player::AttachWeapon()
{
	m_Weapon->IsEnabled(true);
	m_Weapon->IsVisible(true);
	auto *animated_sprite_component = m_Weapon->GetComponentMgr()->GetComponent<AnimatedSpriteComponent>();
	std::string name_with_direction = GetAnimationNameWithOrientation("baton_attack1", GetOrientation());
	animated_sprite_component->SetCurrentAnimation(name_with_direction, true);
}

void Player::UnAttachWeapon()
{
	m_Weapon->IsEnabled(false);
	m_Weapon->IsVisible(false);
}

void Player::SetWeapon(BaseEntity* weapon)
{
	m_Weapon = weapon;
	m_Weapon->SetParent(GetEntity());
}
