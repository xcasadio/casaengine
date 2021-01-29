#include "Base.h"
#include "Enemy.h"
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
	SetController(::new EnemyController(this));
	Character::Initialize();
}