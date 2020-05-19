#include "Base.h"
#include "Enemy.h"
#include "CharacterEnum.h"
#include "CustomComponentType.h"
#include "EnemyController.h"

/**
 * 
 */
Enemy::Enemy(BaseEntity* pEntity) :
	Character(pEntity)
{
}

/**
 * 
 */
Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
	m_pController = ::new EnemyController(this);
	Character::Initialize();
}
